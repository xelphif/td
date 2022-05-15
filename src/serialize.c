#include "serialize.h"

#include <stdio.h>
#include <json-c/json.h>

#include "item.h"
#include "log.h"

char *filename = ".todo.json";

static json_object *json_item_init(item_t *item)
{
    json_object *obj = json_object_new_object();

    json_object_object_add(obj, "text", json_object_new_string(item->text));
    json_object_object_add(obj, "status",
                           json_object_new_boolean(item->status));

    return obj;
}

int file_delete(void)
{
    return !!remove(filename);
}

int serialize(array_t *array)
{
    if (!array->size) {
        LOG_WARN("Empty list, deleting file.")
        file_delete();
        return 1;
    }

    json_object *json_array = json_object_new_array();

    if (!json_array) {
        // LOG_DEBUG(JSON_ERR);
        return 1;
    }

    for (int i = 0; i < array->size; i++)
        json_object_array_add(json_array, json_item_init(array->items[i]));

    json_object_to_file_ext(filename, json_array, JSON_C_TO_STRING_PRETTY);
    json_object_put(json_array);

    return 0;
}

int deserialize(array_t *array)
{
    json_object *json_array = json_object_from_file(filename);

    if (!json_array) {
        // LOG_DEBUG(JSON_ERR);
        return 1;
    }

    size_t json_array_len = json_object_array_length(json_array);
    for (int i = 0; i < json_array_len; i++) {
        json_object *temp   = json_object_array_get_idx(json_array, i);
        json_object *text   = json_object_object_get(temp, "text");
        json_object *status = json_object_object_get(temp, "status");

        a_push(array, item_init(json_object_get_string(text),
                                json_object_get_boolean(status)));
    }

    json_object_put(json_array);

    return 0;
}
