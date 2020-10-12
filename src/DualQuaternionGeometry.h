//
// Created by Max on 10/11/2020.
//

#ifndef DUALQUATERNION_DUALQUATERNIONGEOMETRY_H
#define DUALQUATERNION_DUALQUATERNIONGEOMETRY_H


#include "DualQuaternionBasics.h"

typedef float vertex[3];
typedef float vector3[3];

const dq_t X_AXIS = {0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f};
const dq_t Y_AXIS = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f};
const dq_t Z_AXIS = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f};


void dq_to_vertex(vertex out, const dq_t p);

void dq_from_vertex(dq_t out, const vertex p);

void dq_to_vector(vector3 out, const dq_t p);

void dq_from_vector(dq_t out, const vector3 p);

int dq_is_point(const dq_t p);

int dq_is_vector(const dq_t p);

int dq_is_plane(const dq_t p);

/**
 * @param out   output
 * @param unit  pure unit quaternion that we want to rotate around
 * @param angle HALF of actual rotation angle
 */
void dq_cr_rot_q(dq_t out, const dq_t unit, float halfAngle);

/**
 * @param out   output
 * @param unit  pure unit quaternion that we want to move in
 * @param angle HALF of actual tranlation distance
 */
void dq_cr_tran_q(dq_t out, const dq_t unit, float halfDistance);

#endif //DUALQUATERNION_DUALQUATERNIONGEOMETRY_H