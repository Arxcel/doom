#include "json-builder.h"
#include "map_editor.h"
#include <unistd.h>

int    write_map_to_file(char *buf, const char *filename)
{
    FILE * fp;

    if (!buf || !filename || !(fp = fopen(filename, "w")))
        return (1);
    fprintf(fp, "%s", buf);
    // fclose(fp);
    return (0);
}

int     serialize_map(t_text_sector *sectors, int num_sect)
{
    json_value * obj = json_object_new(3);
    json_value *vert = json_array_new(WALLS_CNT * SECTORS_CNT);
    json_value *arr_sect = json_array_new(num_sect + 1);

    int i = -1;
    while (++i <= num_sect)
    {
        int j = -1;
        json_value *sector = json_object_new(5);

        json_value *vertices = json_array_new(sectors[i].num_walls);
        json_value *neighbors = json_array_new(sectors[i].num_walls);
        json_value *textures = json_array_new(sectors[i].num_walls);

        while (++j < sectors[i].num_walls)
        {
            json_value *_obj = json_object_new(2);
            json_object_push(_obj, "x", json_double_new(sectors[i].wall_vertice[j].begin.x));
            json_object_push(_obj, "y", json_double_new(sectors[i].wall_vertice[j].begin.y));
            json_array_push(vert, _obj);

            json_array_push(vertices, json_integer_new(sectors[i].wall_vertice[j].global_index));
            json_array_push(neighbors, json_integer_new(sectors[i].neighbors[j]));
            json_array_push(textures, json_integer_new(sectors[i].wall_vertice[j].texture));

        }
        json_object_push(sector, "floor_height", json_integer_new(0));
        json_object_push(sector, "ceiling_height", json_integer_new(100));
        json_object_push(sector, "vertices", vertices);
        json_object_push(sector, "neighbors", neighbors);
        json_object_push(sector, "textures", textures);
        json_array_push(arr_sect, sector);
    }
    json_object_push(obj, "vertices", vert);
    json_object_push(obj, "sector", arr_sect);
    char *buf = malloc(json_measure(obj));
    json_serialize(buf, obj);

    printf("%s\n", buf);
    
    write_map_to_file(buf, "maps/test.json");
    // FILE * fp;
    // if (!buf || !(fp = fopen("maps/test.json","w")))
    //     return (1);
    // fprintf(fp, "%s", buf);
    // fclose(fp);
    // free(buf);
    return (0);
}