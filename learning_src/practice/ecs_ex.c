#include <stddef.h>

// Define the position component
typedef struct {
    float x;
    float y;
} Position;

// Define the entity structure
typedef struct {
    int id;
    int num_components;
    void** components;
} Entity;

// Define the movement_system function
void movement_system(Entity* entities, int nums_entities)
{
    for (int i = 0; i < nums_entities; i++) {
        Entity* entity = &entities[i];
        Position* position = (Position*)entity->components[0];
        position->x += 1.0f;
        position->y += 1.0f;
    }
}

// Define the entity manager functions
Entity* create_entity() 
{
    Entity* entity = malloc(sizeof(Entity));
    entity->id = 0;
    entity->num_components = 0;
    entity->components = NULL;
    return entity;
}

void add_component(Entity* entity, void* component)
{
    entity->num_components++;
    entity->components = realloc(entity->components, entity->num_components * sizeof(void*));
    entity->components[entity->num_components - 1] = component;
}

void remove_component(Entity* entity, int component_index)
{
    entity->num_components--;
    for (int i = component_index; i < entity->num_components; i++) {
        entity->components[i] = entity->components[i + 1];
    }
    entity->components = realloc(entity->components, entity->num_components * sizeof(void*));
}

void delete_entity(Entity* entity)
{
    free(entity->components);
    free(entity);
}