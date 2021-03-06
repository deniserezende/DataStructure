//
//  pm_operations.h -> interprets the geofile of the first project of Data Structure II
//  
//
//  Created by Denise F. de Rezende on 12/09/21.
//



#ifndef qry_operations_h
#define qry_operations_h

#include "SVG.h"
#include "TXT.h"
#include "qry_del_m_dm_mud.h"
#include "qry_dmpt_catac.h"
#include "qry_property_lease.h"
#include "qry_mul_hom.h"
#include "output_svg.h"
#include "graphviz_draw.h"
#include "path.h"

type_mMlavltree get_qry_input_and_generate_output(char *qryfilename, char *output_path, char *geo_filename, type_txt txtfile, type_svg svgfile, type_mMlavltree blocks_avl, type_hashtable blocks_table, type_hashtable properties_table, type_hashtable people_table, type_hashtable properties_leases, double viewbox[4]);

#endif /* qry_operations_h */
