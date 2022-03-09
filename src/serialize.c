#include "array.h"
#include "item.h"
#include "serialize.h"

#include <json-c/json.h>


json_object *init_json_object(item_t *item) {
    json_object *obj = json_object_new_object();

    json_object_object_add(obj, "text", json_object_new_string(item->text));
    json_object_object_add(obj, "finished", json_object_new_boolean(item->finished));

    return obj;
}

void serialize(char *filename, array_t *array) {
    json_object *json_array = json_object_new_array();
    for (int i = 0; i < array->size; i++) {
        json_object_array_add(json_array, init_json_object(array->items[i]));
    }

    json_object_to_file_ext(filename, json_array, JSON_C_TO_STRING_PRETTY);

    json_object_put(json_array);
}

int deserialize(char* filename, array_t *array) {
    json_object *json_array = json_object_from_file(filename);
    if (!json_array)
        return 1;

    size_t json_array_len = json_object_array_length(json_array);

    for (int i = 0; i < json_array_len; i++) {
        json_object *temp = json_object_array_get_idx(json_array, i);
        json_object *text = json_object_object_get(temp, "text");
        json_object *finished = json_object_object_get(temp, "finished");

        a_add(array,
                init_item(
                    json_object_get_string(text),
                    json_object_get_string_len(text),
                    json_object_get_boolean(finished)
                    )
                );
    }

    json_object_put(json_array);
    return 0;
}
