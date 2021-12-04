
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "strongly_connected_components_algorithm.h" 

typedef struct dfs_data{
	// depth first search
	int DFS_visited;
    int DFS_starting_time;
    int DFS_finnishing_time;
	int DFS_id;
	int DFS_component;
}DFS_DATA;

typedef struct vertex_aux_data{
	// depth first search
	int dfs_visited;
    int dfs_starting_time;
    int dfs_finnishing_time;

	// breadth first search
	long bfs_tmp_value;
	long bfs_def_value;
	struct vertex *bfs_from_vertex;
}DATA;

typedef struct vertex{
	char id[41];
	type_graphinfos *vertex_info;
	type_list edges;
	DATA *other_data;
	DFS_DATA* data_for_other_algorithms;
}VERTEX;

typedef struct edge{
	VERTEX *to;
	type_graphinfos* edge_info;
}EDGE;

typedef struct graph{
	type_list vertices; // VERTEX
	int current_size; // amount of vertices
	int amount_of_edges;
}GRAPH;

int *SCCA_finishing_time;
int *SCCA_order;
int *SCCA_backorder;
int *SCCA_solution;
int SCCA_index;

int DFS_time;
int DFS_done;
int DFS_index_components;


void _DFS_traverse_graph_verticies_with_action(type_graph graph, type_graphptrf_onetypeinfo action){
	GRAPH *graph_ = graph; 
	if(graph_ == NULL) return;
	
	if(empty_list(graph_->vertices)){
		printf("Graph is empty.\n"); 
        return;
	}

	set_current_to_first_item_in_list(graph_->vertices);
	int done;
	do{
		done = is_current_last_item_in_list(graph_->vertices);
		VERTEX *current_vertex = get_current_item_in_list(graph_->vertices);
		action(current_vertex);
		move_current_forward_in_list(graph_->vertices);
	}while (!done);
	return;	
}


void _DFS_depth_first_search_visit_start(VERTEX* vertex){
	DFS_time++;
	vertex->data_for_other_algorithms->DFS_visited = 1;
	vertex->data_for_other_algorithms->DFS_starting_time = DFS_time;

	printf("id=%s\n",vertex->id);
	printf("st=%d\n", vertex->data_for_other_algorithms->DFS_starting_time);
	printf("---------------\n");
}

void _DFS_depth_first_search_visit_finnish(VERTEX* vertex){
	DFS_time++;
	vertex->data_for_other_algorithms->DFS_finnishing_time = DFS_time;
	printf("id=%s\n",vertex->id);
	printf("ft=%d\n", vertex->data_for_other_algorithms->DFS_finnishing_time);
	printf("---------------\n");
}


void _DFS_set_up_depth_first_search_traversal_with_actions_in_graph_action(VERTEX* vertex){
	vertex->data_for_other_algorithms->DFS_visited = 0;
	vertex->data_for_other_algorithms->DFS_starting_time = 0;
	vertex->data_for_other_algorithms->DFS_finnishing_time = 0;
}

void _DFS_set_up_depth_first_search_traversal_with_actions_in_graph(type_graph graph){
	DFS_time = 0;
	_DFS_traverse_graph_verticies_with_action(graph, (void*)_DFS_set_up_depth_first_search_traversal_with_actions_in_graph_action);
}


VERTEX* _DFS_find_unvisited_vertex_for_depth_first_search(GRAPH* graph, int order[], int next){//, int *new_i){
    int done;
	size_t n = graph->current_size;
	printf("next=%d\tsize=%zu\n", next, n);
	//*new_i = next;
	if(next >= n) return NULL;
	printf("order[next]=%d\n", order[next]);

	set_current_to_first_item_in_list(graph->vertices);
	for(int j = 0; j < order[next]; j++){
		move_current_forward_in_list(graph->vertices);
	}

	VERTEX * current_vertex = get_current_item_in_list(graph->vertices);
	printf("idnext=%s\n", current_vertex->id);
	if(current_vertex->data_for_other_algorithms->DFS_visited == 0) return current_vertex;
	return NULL;
	//return _DFS_find_unvisited_vertex_for_depth_first_search(graph, order, next + 1, new_i);
}

VERTEX* next_vertex_pointed_by_from_vertex(VERTEX* from_vertex){
	set_current_to_first_item_in_list(from_vertex->edges);
	EDGE* edge;
	int done;
	do{
		done = is_current_last_item_in_list(from_vertex->edges);
		edge = get_current_item_in_list(from_vertex->edges);
		if((edge->to)->data_for_other_algorithms->DFS_visited == 0){
			printf("%s\t", (edge->to)->id);
			printf("supostamente encontrie\n");
			break;
		}
		move_current_forward_in_list(from_vertex->edges);
	}while(!done);
	return edge->to;
}


void _DFS_(VERTEX* vertex, type_lptrf_oneitem vertex_action_one, type_lptrf_oneitem vertex_action_two){
	printf("no _DFS_\n");

	//_DFS_depth_first_search_visit_start(vertex);
	printf("vertex=%s\n", vertex->id);
	vertex_action_one(vertex);

	if(vertex->edges == NULL || empty_list(vertex->edges)){
		//_DFS_depth_first_search_visit_finnish(vertex);
		vertex_action_two(vertex);
		return; // stuck
	}
	
	set_current_to_first_item_in_list(vertex->edges);
	EDGE* edge;
	int done;
	do{
		done = is_current_last_item_in_list(vertex->edges);
		edge = get_current_item_in_list(vertex->edges);
		if((edge->to)->data_for_other_algorithms->DFS_visited == 0){
			printf("%s\t", (edge->to)->id);
			printf("supostamente encontrie\n");
			VERTEX* next_vertex = edge->to;
			_DFS_(next_vertex, vertex_action_one, vertex_action_two);
		}
		move_current_forward_in_list(vertex->edges);
	}while(!done);

	// next_vertex = edge->to;
    //_DFS_(vertex, vertex_action_one, vertex_action_two);
	printf("vou para o _DFS_depth_first_search_visit_finnish\n");
	//_DFS_depth_first_search_visit_finnish(vertex);
	vertex_action_two(vertex);
	return;
}


void _DFS_depth_first_search_with_actions_in_graph(type_graph graph, int order[], type_lptrf_oneitem vertex_action_one, type_lptrf_oneitem vertex_action_two){
	GRAPH *graph_ = graph; 
	if(graph_ == NULL || empty_graph(graph_)) return;
	_DFS_set_up_depth_first_search_traversal_with_actions_in_graph(graph_);

    DFS_index_components = 0;
    //int new_i;
    for(int i=0; i < graph_->current_size; i++){
	printf("\n\nMudando de componente conexa\n");
	    VERTEX* vertex = _DFS_find_unvisited_vertex_for_depth_first_search(graph, order, i);//, &new_i);
		printf("i=%d\n", i);
        if(vertex == NULL) continue;//break;
        _DFS_(vertex, vertex_action_one, vertex_action_two);
        DFS_index_components++;
    }
    
}











long _SCCA_reverse_graph_vertex_condition(type_graphinfos vertex){
    return 1;
}

long _SCCA_reverse_graph_edge_condition(type_graphinfos from_vertex, type_graphinfos edge, type_graphinfos to_vertex){
    return 1;
}

void _set_up_vector_order(VERTEX* vertex){
	vertex->data_for_other_algorithms = malloc(sizeof(DFS_DATA));
	vertex->data_for_other_algorithms->DFS_id = SCCA_index;
    SCCA_order[SCCA_index] = vertex->data_for_other_algorithms->DFS_id;
	printf("vertexid=%s\t vertexidint=%d\n", vertex->id, vertex->data_for_other_algorithms->DFS_id);
    SCCA_index++;
}

void _set_up_reversed_graph(VERTEX* vertex){
	vertex->data_for_other_algorithms = malloc(sizeof(DFS_DATA));
}

void _saving_computed_finishing_time(VERTEX* vertex){
	_DFS_depth_first_search_visit_finnish(vertex);
    SCCA_finishing_time[SCCA_index] = vertex->data_for_other_algorithms->DFS_finnishing_time;
    SCCA_backorder[SCCA_index] = vertex->data_for_other_algorithms->DFS_id;
    SCCA_index++;
}

void _SCCA_return(VERTEX* vertex){
	_DFS_depth_first_search_visit_start(vertex);
    return;
}

void _SCCA_output_ending(VERTEX* vertex){
    vertex->data_for_other_algorithms->DFS_component = DFS_index_components;
	printf("-[%d]\n", DFS_index_components);
}

void _SCCA_create_backorder(int finishing_time[], int backorder[], int size){
    // selection sort
	int j, biggest, save_value_of_i, i, tmp;
	
    for(j = 0; j < size; j++){
		biggest = finishing_time[j];
		save_value_of_i = j;

		for(i = j; i < size; i++){
			if(finishing_time[i] > biggest){
				biggest = finishing_time[i];
				save_value_of_i = i;
			}
		}

		tmp = finishing_time[j];
		finishing_time[j] = finishing_time[save_value_of_i];
		finishing_time[save_value_of_i] = tmp;
        
		tmp = backorder[j];
		backorder[j] = backorder[save_value_of_i];
		backorder[save_value_of_i] = tmp;
	}
}

void _set_up_solution_vertex(VERTEX* vertex){
	SCCA_solution[SCCA_index] = vertex->data_for_other_algorithms->DFS_component;
	printf("%d\n", vertex->data_for_other_algorithms->DFS_component);
	SCCA_index++;
}

void strongly_connected_components_algorithm(type_graph graph, int *solution_vector){
	printf("iniciando\n");
    GRAPH* graph_ = graph;
    int order[graph_->current_size];
    int backorder[graph_->current_size];
    int finishing_time[graph_->current_size];

    SCCA_order = order;
    SCCA_backorder = backorder;
    SCCA_finishing_time = finishing_time;
	SCCA_solution = solution_vector;

    SCCA_index = 0;
    _DFS_traverse_graph_verticies_with_action(graph_, (void*)_set_up_vector_order);
	printf("depois do _DFS_traverse_graph_verticies_with_action 1\n");
    SCCA_index = 0;
// 1 call DFS.G/ to compute finishing times u:f for each vertex u 
    _DFS_depth_first_search_with_actions_in_graph(graph_, order, (void*)_SCCA_return, (void*)_saving_computed_finishing_time);
	printf("depois do _DFS_depth_first_search_with_actions_in_graph\n");

// 2 compute GT
    type_graph reversed_graph = create_reverse_graph_with_conditionals(graph, (void*)_SCCA_reverse_graph_vertex_condition, (void*)_SCCA_reverse_graph_edge_condition);
	printf("depois do create_reverse_graph_with_conditionals\n");

    _SCCA_create_backorder(finishing_time, backorder, graph_->current_size);
	printf("depois do _SCCA_create_backorder\n");
	
	printf("backorder\n");
	for(int k=0; k < graph_->current_size; k++){
		printf("%d\t", backorder[k]);
	}

// 3 call DFS.GT/, but in the main loop of DFS, consider the vertices in order of decreasing u:f (as computed in line 1)
    _DFS_traverse_graph_verticies_with_action(reversed_graph, (void*)_set_up_reversed_graph);
	_DFS_depth_first_search_with_actions_in_graph(reversed_graph, backorder, (void*)_SCCA_return, (void*)_SCCA_output_ending);
	printf("depois do _DFS_depth_first_search_with_actions_in_graph\n");

	//aquide tem que fazer o cleanup

// 4 output the vertices of each tree in the depth-first forest formed in line 3 as a separate strongly connected component
    // criar um grafo com as componentes
    // e colocar em um vetor a qual componente pertence
	SCCA_index = 0;
	_DFS_traverse_graph_verticies_with_action(reversed_graph, (void*)_set_up_solution_vertex);
	printf("depois do _DFS_traverse_graph_verticies_with_action\n");

    return;
}







