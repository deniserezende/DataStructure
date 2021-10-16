//
//  output_svg.h -> Used for the second project of Data Structure
//  
//
//  Created by Denise F. de Rezende on 18/09/21.
//

#ifndef output_svg_h
#define output_svg_h

#include "SVG.h"
#include "hash_table.h"
#include "mM_avl_tree_wlist.h"
#include "rectangle.h"
#include "block.h"
#include "property.h"
#include "person.h"



// Insert blocks in svg
void insert_blocks_in_svg(type_svg svgfile, type_mMlavltree blocks);

// Insert people in svg
void insert_people_in_svg(type_svg svgfile, type_hashtable people, type_hashtable blocks);

// Insert residences in svg
void insert_properties_in_svg(type_svg svgfile, type_hashtable properties, type_hashtable blocks);

#endif /* output_svg_h */