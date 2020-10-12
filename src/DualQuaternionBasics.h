//
// Created by Max on 10/9/2020.
//

#ifndef DUALQUATERNION_DUALQUATERNIONBASICS_H
#define DUALQUATERNION_DUALQUATERNIONBASICS_H

/**
 * the dual quaternion indexes correspond to:
 * 0-3 first quaternion q1, 4-7 second quaternion q2,
 * where for both q1 and q2, q = [i, j, k, c]
 */
typedef float dq_t[8];

typedef float q_t[4];

// Note that for most of the following functions, we can still have mutation
// by passing the same DQ for the input and out

void dq_add(dq_t out, const dq_t p, const dq_t q);

void dq_minus(dq_t out, const dq_t p, const dq_t q);

void dq_scale(dq_t out, float c, const dq_t p);

void dq_conj_star(dq_t out, const dq_t p);

void dq_conj_bar(dq_t out, const dq_t p);

void dq_conj_cross(dq_t out, const dq_t p);


// For the following, DO NOT use out for mutations!!!
void q_mult(q_t out, const q_t p, const q_t q);
void q_add(q_t out, const q_t p, const q_t q);

void dq_mult(dq_t out, const dq_t p, const dq_t q);

void dq_sandwhich_map(dq_t out, const dq_t Q, const dq_t p);

// result is a dual real. However, in a lot of situations we only care about the real part.
float dq_dot(float * dual, const dq_t p, const dq_t q);


#endif //DUALQUATERNION_DUALQUATERNIONBASICS_H
