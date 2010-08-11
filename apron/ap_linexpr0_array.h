/* ************************************************************************* */
/* ap_linexpr0_array.h: array of linear expressions */
/* ************************************************************************* */

/* This file is part of the APRON Library, released under LGPL license.  Please
   read the COPYING file packaged in the distribution */

/* normally included from ap_expr0.h */

#ifndef _AP_LINEXPR0_ARRAY_H_
#define _AP_LINEXPR0_ARRAY_H_

#include "ap_linexpr0.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ====================================================================== */
/* Datatypes */
/* ====================================================================== */

/* Array of linear expressions */
typedef struct ap_linexpr0_array_struct {
  bool ref;
  ap_scalar_discr_t discr;
  union {
    itvD_linexpr_array_ptr    D;
    itvMPQ_linexpr_array_ptr  MPQ;
    itvMPFR_linexpr_array_ptr MPFR;
  } linexpr_array;
} ap_linexpr0_array_struct;
typedef ap_linexpr0_array_struct ap_linexpr0_array_t[1];
typedef ap_linexpr0_array_struct* ap_linexpr0_array_ptr;

/* ====================================================================== */
/* I. Memory management and printing */
/* ====================================================================== */

void ap_linexpr0_array_init(ap_linexpr0_array_t e, ap_scalar_discr_t discr, size_t size);
void ap_linexpr0_array_init_set(ap_linexpr0_array_t res, ap_linexpr0_array_t e);
static inline void ap_linexpr0_array_init_cons_D(ap_linexpr0_array_t res, itvD_linexpr_array_t e);
static inline void ap_linexpr0_array_init_cons_MPQ(ap_linexpr0_array_t res, itvMPQ_linexpr_array_t e);
static inline void ap_linexpr0_array_init_cons_MPFR(ap_linexpr0_array_t res, itvMPFR_linexpr_array_t e);

void ap_linexpr0_array_minimize(ap_linexpr0_array_t a);
void ap_linexpr0_array_clear(ap_linexpr0_array_t e);
void ap_linexpr0_array_fprint(FILE* stream, ap_linexpr0_array_t e, char** name_of_dim);

static inline void ap_linexpr0_array_ref_D(ap_linexpr0_array_t res, itvD_linexpr_array_t e);
static inline void ap_linexpr0_array_ref_MPQ(ap_linexpr0_array_t res, itvMPQ_linexpr_array_t e);
static inline void ap_linexpr0_array_ref_MPFR(ap_linexpr0_array_t res, itvMPFR_linexpr_array_t e);
  /* Returns a reference on the argument under the form of ap_linexpr0_ref.
     INTERNAL USE.
     BE CAUTIOUS: memory is shared between the result and the argument, and
     memory should be managed through the argument. */

/* ====================================================================== */
/* II. Conversions */
/* ====================================================================== */

bool ap_linexpr0_array_set(ap_linexpr0_array_t res, ap_linexpr0_array_t e, numinternal_t intern);

bool ap_linexpr0_array_set_itvD_linexpr(ap_linexpr0_array_t a, itvD_linexpr_array_t b, numinternal_t intern);
bool ap_linexpr0_array_set_itvMPQ_linexpr(ap_linexpr0_array_t a, itvMPQ_linexpr_array_t b, numinternal_t intern);
bool ap_linexpr0_array_set_itvMPFR_linexpr(ap_linexpr0_array_t a, itvMPFR_linexpr_array_t b, numinternal_t intern);

bool itvD_linexpr_array_set_ap_linexpr0_array(itvD_linexpr_array_t a, ap_linexpr0_array_t b, numinternal_t intern);
bool itvDMPQ_linexpr_array_set_ap_linexpr0_array(itvMPQ_linexpr_array_t a, ap_linexpr0_array_t b, numinternal_t intern);
bool itvMPFR_linexpr_array_set_ap_linexpr0_array(itvMPFR_linexpr_array_t a, ap_linexpr0_array_t b, numinternal_t intern);

/* ====================================================================== */
/* III. Access */
/* ====================================================================== */

size_t ap_linexpr0_array_size(ap_linexpr0_array_t p);
itvlinexpr_type_t ap_linexpr0_array_type(ap_linexpr0_array_t array);
bool ap_linexpr0_array_is_linear(ap_linexpr0_array_t array);
bool ap_linexpr0_array_is_quasilinear(ap_linexpr0_array_t array);
  /* Are all the constraints involved linear (resp. quasilinear) */

void ap_linexpr0_array_ref_index(ap_linexpr0_t a, ap_linexpr0_array_t p, size_t i);

bool ap_linexpr0_array_get_index(ap_linexpr0_t a, ap_linexpr0_array_t p, size_t i, numinternal_t intern);
bool ap_linexpr0_array_set_index(ap_linexpr0_array_t p, size_t i, ap_linexpr0_t a, numinternal_t intern);

/* ====================================================================== */
/* IV. Change of dimensions and permutations */
/* ====================================================================== */

/* This function add dimensions to the expressions, following the
   semantics of dimchange (see the type definition of dimchange).  */
void ap_linexpr0_array_add_dimensions(ap_linexpr0_array_t a,
				      ap_linexpr0_array_t b,
				      ap_dimchange_t* dimchange);

/* This function apply the given permutation to the dimensions. If dense
   representation, the size of the permutation should be expr->size. If sparse
   representation, the dimensions present in the expression should just be less
   than the size of the permutation. */
void ap_linexpr0_array_permute_dimensions(ap_linexpr0_array_t a,
					  ap_linexpr0_array_t b,
					  ap_dimperm_t* perm);

static inline void ap_linexpr0_array_init_cons_D(ap_linexpr0_array_t res, itvD_linexpr_array_t e)
{ res->ref = false; res->discr = AP_SCALAR_D; res->linexpr_array.D = e; };
static inline void ap_linexpr0_array_init_cons_MPQ(ap_linexpr0_array_t res, itvMPQ_linexpr_array_t e)
{ res->ref = false; res->discr = AP_SCALAR_MPQ; res->linexpr_array.MPQ = e; };
static inline void ap_linexpr0_array_init_cons_MPFR(ap_linexpr0_array_t res, itvMPFR_linexpr_array_t e)
{ res->ref = false; res->discr = AP_SCALAR_MPFR; res->linexpr_array.MPFR = e; };

static inline void ap_linexpr0_array_ref_D(ap_linexpr0_array_t res, itvD_linexpr_array_t e)
{ res->ref = true; res->discr = AP_SCALAR_D; res->linexpr_array.D = e; };
static inline void ap_linexpr0_array_ref_MPQ(ap_linexpr0_array_t res, itvMPQ_linexpr_array_t e)
{ res->ref = true; res->discr = AP_SCALAR_MPQ; res->linexpr_array.MPQ = e; };
static inline void ap_linexpr0_array_ref_MPFR(ap_linexpr0_array_t res, itvMPFR_linexpr_array_t e)
{ res->ref = true; res->discr = AP_SCALAR_MPFR; res->linexpr_array.MPFR = e; };

#ifdef __cplusplus
}
#endif

#endif