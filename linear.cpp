#include "linear.h"
#include "problem_structs.h"

int linear_solve(problem& p, int max_papers, int min_reviewers) {
	unsigned int obj_num = p.objects.size();
	unsigned int age_num = p.agents.size();
	glp_prob *lp;
	lp = glp_create_prob();
	int* ri = (int*) calloc(1 + (obj_num+age_num)*(obj_num*age_num), sizeof(unsigned int));
	int* ci = (int*) calloc(1 + (obj_num+age_num)*(obj_num*age_num), sizeof(unsigned int));
	double* vals = (double*) calloc(1 + (obj_num+age_num)*(obj_num*age_num), sizeof(double)); //ojects i, agents j
	//index will be [i*age_num + j]
	glp_add_cols(lp, obj_num*age_num); //for each combination
	glp_add_rows(lp, obj_num+age_num); //for each thingy

	for(unsigned int i = 0; i < obj_num; i++) {
		glp_set_row_bnds(lp, 1+i, GLP_DB, min_reviewers, 1000.0);
	}
	for(unsigned int i = obj_num; i < age_num+obj_num; i++) {
		glp_set_row_bnds(lp, 1+i, GLP_DB, 0.0, max_papers);
	}
	for(unsigned int i = 0; i < obj_num; i++) {
		for(unsigned int j = 0; j < age_num; j++) {
			glp_set_col_bnds(lp, (1 + i*age_num + j), GLP_DB, 0.0, 1.0);
			glp_set_obj_coef(lp, (1 + i*age_num + j), p.agents[j].values[i]);
			for(unsigned int k = 0; k < age_num+obj_num; k++) {
				ri[1 + k*obj_num*age_num + (i*age_num + j)] = 1 + k;
				ci[1 + k*obj_num*age_num + (i*age_num + j)] = 1 + (i*age_num + j);
				if((i == k) || (j+obj_num == k)) {
					vals[1 + k*obj_num*age_num + (i*age_num + j)] = 1.0;
				} else {
					vals[1 + k*obj_num*age_num + (i*age_num + j)] = 0.0;
				}
			}
		}
	}
	glp_load_matrix(lp, (obj_num*age_num)*(obj_num+age_num), ri, ci, vals);
	glp_set_obj_dir(lp, GLP_MAX);  //we maximizing boiz
	glp_smcp param;
	glp_init_smcp(&param);
	param.msg_lev = GLP_MSG_OFF;
	glp_simplex(lp, &param);
	for(unsigned int i = 0; i < obj_num; i++) {
		for(unsigned int j = 0; j < age_num; j++) {
			if(glp_get_col_prim(lp, 1 + (i*age_num + j))) {
				p.agents[j].held.push_back(i);
				p.objects[i].held_by.push_back(j);
			}
		}
	}
	glp_delete_prob(lp);
  	glp_free_env();
  	free(ri);
  	free(ci);
  	free(vals);
	//std::cout << glp_get_obj_val(lp) << std::endl;
	return 0;
	// row's 
}