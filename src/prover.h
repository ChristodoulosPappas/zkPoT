#pragma once

#include "circuit.h"
#include <vector>
#include <ctime>
#include <algorithm>
#include <memory>
#include "config_pc.hpp"
#include "polynomial.h"
#include "timer.hpp"
using std::unique_ptr;
class prover
{
public:
	explicit prover(const layeredCircuit &cir, char *filename,vector<F> &data, bool d);
	//void evaluate(char *filename);
	void evaluate(char *filename,vector<F> &data);
    void init();
    void sumcheckInitAll(const vector<F>::const_iterator &r_last);
    void sumcheckInit();
    void sumcheckInitPhase1(const F &assert_random);
	void sumcheckInitPhase2();
    void sumcheckInitLiu(vector<F>::const_iterator s);

	quadratic_poly sumcheckUpdatePhase1(const F &previousRandom);
	quadratic_poly sumcheckUpdatePhase2(const F &previousRandom);
	quadratic_poly sumcheckLiuUpdate(const F &previousRandom);

    void sumcheckFinalize1(const F &previousRandom, F &claim);
    void sumcheckFinalize2(const F &previousRandom, vector<F>::iterator claims);
    void sumcheckLiuFinalize(const F &previousRandom, F &claim);
    void compute_witness_points(vector<F> &computations,vector<F> r_liu, int segment_size);
    void delete_data(){
        for(int i = 0; i < circuitValue.size(); i++){
            vector<F>().swap(circuitValue[i]);
        }
        for(int i = 0; i < multArray.size(); i++){
            vector<linear_poly>().swap(multArray[i]);
            
        }
        for(int i = 0; i < addVArray.size(); i++){
            vector<linear_poly>().swap(addVArray[i]);
            
        }
        for(int i = 0; i < Vmult.size(); i++){
            vector<linear_poly>().swap(Vmult[i]);
            
        }
        vector<vector<linear_poly>>().swap(multArray);
        vector<vector<linear_poly>>().swap(addVArray);
        vector<vector<linear_poly>>().swap(Vmult);
        vector<vector<F>>().swap(circuitValue);
        vector<F>().swap(beta_g);
        vector<F>().swap(beta_u);
    
    }
    F Vres(const vector<F>::const_iterator &r_0, int r_0_size);

	double proveTime() const;
	double proofSize() const;

#ifdef USE_VIRGO
	virgo::poly_commit::poly_commit_prover poly_prover[16];
	void commit_private_segmented(vector<virgo::__hhash_digest> &hashes,int segment_size);
    virgo::__hhash_digest commit_private_segment(int segment_size, int i);
    virgo::__hhash_digest commit_private();
	F inner_prod(const vector<F> &a, const vector<F> &b, u64 l);
	virgo::__hhash_digest commit_public(vector<F> &pub, F &inner_product_sum, std::vector<F> &mask, vector<F> &all_sum);
    virgo::__hhash_digest commit_public(vector<F> &pub, F &inner_product_sum, std::vector<F> &mask, vector<F> &all_sum,int i,int segment_size);
#endif

private:
    quadratic_poly sumcheckUpdate(const F &previous_random, vector<F> &r_arr, int n_pre_layer);
    quadratic_poly sumcheckUpdateEach(const F &previous_random, int idx);

    const layeredCircuit &C;
    vector<vector<F>> circuitValue;

    vector<F> r_u, r_liu;
    vector<vector<F>> r_v;

    vector<F> beta_g;
    vector<F> beta_u;
    vector<u64> total;
    vector<u64> totalSize;

    int round;
    int sumcheckLayerId;
    vector<vector<linear_poly>> multArray, addVArray, Vmult;
    F add_term = F_ZERO, V_u = F_ZERO;

    timer prove_timer;
    u64 proof_size;

};
