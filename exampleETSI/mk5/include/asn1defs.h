/* 
 * ASN1 definitions (application visible) 
 * Copyright (C) 2011-2018 Fabrice Bellard
*/
#ifndef _ASN1_DEFS_H
#define _ASN1_DEFS_H

#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <math.h>

#if defined(_MSC_VER)
#define inline __inline
#endif

#ifdef  __cplusplus
extern "C" {
#endif

/* define it to include support for arbitrary length integers
   (otherwise integers of at most 32 bits are supported) */
#define ASN1_USE_LARGE_INTEGER

/* define it to enable the asn1_exception warning */
//#define ASN1_USE_ASN1_WARN_UNUSED_RESULT

#ifdef ASN1_USE_ASN1_WARN_UNUSED_RESULT
#define asn1_exception __attribute__((warn_unused_result))
#else
#define asn1_exception
#endif

#ifndef offsetof
#define offsetof(type, field) ((size_t) &((type *)0)->field)
#endif

#ifndef _BOOL_defined
#define _BOOL_defined

typedef int BOOL;
enum {
    FALSE = 0,
    TRUE = 1,
};
#endif

/* Used for:
   OCTET STRING: len is in bytes
   SEQUENCE OF: len is a number of items buf contains len * sizeof(struct) bytes
*/
typedef struct ASN1String {
    uint8_t *buf;
    size_t len;
} ASN1String;

typedef struct ASN1BitString {
    uint8_t *buf;
    size_t len; /* len is in bits. buf contains ceil(len/8) bytes */
} ASN1BitString;

typedef struct ASN1BMPString {
    uint16_t *buf;
    size_t len;
} ASN1BMPString;

typedef struct ASN1UniversalString {
    uint32_t *buf;
    size_t len;
} ASN1UniversalString;

typedef ASN1String ASN1ObjectIdentifier;
typedef ASN1String ASN1RelativeOID;
typedef uint8_t ASN1Null;

/* Note: could be extended to 64 bit when needed */
#define ASN1_LIMB_BITS_LOG2 5
#define ASN1_LIMB_BITS (1 << ASN1_LIMB_BITS_LOG2)
#define ASN1_LIMB_BYTES (1 << (ASN1_LIMB_BITS_LOG2 - 3))

typedef uint32_t ASN1Limb;

typedef struct ASN1Integer {
    ASN1Limb *data;
    uint32_t len; /* 0 is represented as len = 0 and negative = 0 or 1 */
    uint32_t allocated_len; /* length (>= len) allocated for tab */
    int negative; /* 0 = positive, 1 = negative */
} ASN1Integer;

/* compressed ASN1 type definition */
typedef uintptr_t ASN1CType;

typedef struct ASN1OpenType {
    ASN1CType *type; /* if the 'type' is NULL, 'octet_string' contains
                        the raw content. Otherwise, 'data' is the
                        corresponding value. */
    union {
        void *data;
        ASN1String octet_string;
    } u;
} ASN1OpenType;

typedef intptr_t asn1_ssize_t; /* signed size_t */
    
#define ASN1_CTYPE_SHIFT 27
#define ASN1_CTYPE_HAS_NAME (1 << 26) /* explicit type name is present */
#define ASN1_CTYPE_HAS_EXT  (1 << 25)
#define ASN1_CTYPE_HAS_LOW  (1 << 24) /* lower end present */
#define ASN1_CTYPE_HAS_HIGH (1 << 23) /* high end present */
#define ASN1_CTYPE_HAS_LARGE (1 << 22) /* large integer */
#define ASN1_CTYPE_HAS_EXPLICIT (1 << 25) /* for ASN1_CTYPE_TAGGED */
#define ASN1_CTYPE_HAS_POINTER  (1 << 24) /* for ASN1_CTYPE_TAGGED */
#define ASN1_CTYPE_HAS_ROOT_AFTER_EXT (1 << 24) /* for ASN1_CTYPE_SEQUENCE */
#define ASN1_CTYPE_HAS_CONSTRAINT (1 << 21)
#define ASN1_CTYPE_HAS_CONV_TABLE (1 << 24) /* for ASN1_CTYPE_ENUMERATED */

#define ASN1_TAG_BITS 21
#define ASN1_TAG_CLASS_SHIFT (ASN1_TAG_BITS - 2)
#define ASN1_TAG_MAX ((1 << ASN1_TAG_CLASS_SHIFT) - 1)
#define ASN1_GET_CTYPE(x) ((uint32_t)(x) >> ASN1_CTYPE_SHIFT)
#define ASN1_GET_TAG(x) ((x) & ((1 << ASN1_TAG_BITS) - 1))


/* tag classes */
#define ASN1_TAG_UNIVERSAL   (0 << ASN1_TAG_CLASS_SHIFT)
#define ASN1_TAG_APPLICATION (1 << ASN1_TAG_CLASS_SHIFT)
#define ASN1_TAG_CONTEXT     (2 << ASN1_TAG_CLASS_SHIFT)
#define ASN1_TAG_PRIVATE     (3 << ASN1_TAG_CLASS_SHIFT)

#define ASN1_NO_TAG 0

enum {
    ASN1_CTYPE_SEQUENCE,
    ASN1_CTYPE_SEQUENCE_OF,
    ASN1_CTYPE_SET,
    ASN1_CTYPE_SET_OF,
    ASN1_CTYPE_CHOICE,
    ASN1_CTYPE_INTEGER,
    ASN1_CTYPE_BOOLEAN,
    ASN1_CTYPE_BIT_STRING,
    ASN1_CTYPE_OCTET_STRING,
    ASN1_CTYPE_ENUMERATED,
    ASN1_CTYPE_NULL,
    ASN1_CTYPE_TAGGED, /* set implicit or explicit tag */
    ASN1_CTYPE_OBJECT_IDENTIFIER, 
    ASN1_CTYPE_RELATIVE_OID, 
    ASN1_CTYPE_REAL, 
    ASN1_CTYPE_CHAR_STRING, 
    ASN1_CTYPE_ANY, 
    ASN1_CTYPE_OBJECT_CLASS, 
    
    ASN1_CTYPE_COUNT,
};

/* char string sub types */
enum {
    /* restricted multiplier strings first */
    ASN1_CSTR_NumericString,
    ASN1_CSTR_PrintableString,
    ASN1_CSTR_VisibleString,
    ASN1_CSTR_IA5String,
    ASN1_CSTR_BMPString,
    ASN1_CSTR_UniversalString,

    /* then the other strings */
    ASN1_CSTR_UTF8String,
    ASN1_CSTR_GeneralString,
    ASN1_CSTR_GraphicString,
    ASN1_CSTR_TeletexString,
    ASN1_CSTR_VideotexString,

    ASN1_CSTR_COUNT,
};

typedef struct {
    ASN1CType offset; /* offset and component flags */
    ASN1CType *type;
    union {
        uint32_t default_value; /* for BOOLEAN, ENUMERATED and 32 bit
                                   INTEGER */
        ASN1CType option_offset;
        void *default_value_ptr;
    } u;
    char *name;
} ASN1SequenceField;

typedef struct {
    ASN1CType *type;
    char *name;
} ASN1ChoiceField;

typedef struct {
    ASN1CType elem_size;
    ASN1CType *type;
    char *name;
} ASN1SequenceOfCType;

typedef struct ASN1Error {
    int line_num; /* used for GSER decoding */
    int bit_pos; /* used for PER decoding */
    char type_path[256]; /* ASN1 type path */
    char msg[256]; /* message */
} ASN1Error;

#define SEQ_FIELD_LEN (sizeof(ASN1SequenceField) / sizeof(ASN1CType))

#define ASN1_SEQ_FLAG_SHIFT           27
#define ASN1_SEQ_FLAG_NORMAL    0
#define ASN1_SEQ_FLAG_OPTIONAL  1
#define ASN1_SEQ_FLAG_DEFAULT   2

#define ASN1_SEQ_FLAG_EXT             (1U << 29)
#define ASN1_SEQ_FLAG_EXT_GROUP_START (1U << 30)
#define ASN1_SEQ_FLAG_EXT_GROUP_END   (1U << 31)

#define ASN1_GET_SEQ_FLAG(f) (((f)->offset >> ASN1_SEQ_FLAG_SHIFT) & 3)
#define ASN1_GET_SEQ_OFFSET(f) ((f)->offset & ((1 << ASN1_SEQ_FLAG_SHIFT) - 1))
#define ASN1_IS_SEQ_EXT(f) ((f)->offset & ASN1_SEQ_FLAG_EXT)
#define ASN1_IS_SEQ_EXT_GROUP_START(f) ((f)->offset & ASN1_SEQ_FLAG_EXT_GROUP_START)
#define ASN1_IS_SEQ_EXT_GROUP_END(f) ((f)->offset & ASN1_SEQ_FLAG_EXT_GROUP_END)

/* constraints */
enum {
    ASN1_CCONSTRAINT_TABLE,
    ASN1_CCONSTRAINT_CONTAINING,
};

typedef struct {
    uintptr_t type;
    ASN1CType *class_type;
    uintptr_t class_field_index;
    void *objset;
    uintptr_t objset_count;
} ASN1CConstraintTable;

typedef struct {
    uintptr_t type;
    ASN1CType *containing_type;
} ASN1CConstraintContaining;

/* object class */

enum {
    ASN1_CCLASS_FIELD_TYPE,
    ASN1_CCLASS_FIELD_FIXED_TYPE_VALUE, /* also for objects */
    ASN1_CCLASS_FIELD_FIXED_TYPE_VALUE_SET, /* also for objects */
    ASN1_CCLASS_FIELD_VAR_TYPE_VALUE,
    ASN1_CCLASS_FIELD_VAR_TYPE_VALUE_SET,
};

#define ASN1_CCLASS_FIELD_GET_TYPE(x) ((x) & 0x7)
#define ASN1_CCLASS_FIELD_FLAG_SHIFT 3
#define ASN1_CCLASS_FIELD_GET_FLAG(x) (((x) >> ASN1_CCLASS_FIELD_FLAG_SHIFT) & 3)

typedef struct {
    ASN1CType flags;
    ASN1CType *type;
    void *default_value;
    const char *name;
} ASN1CClassField;

/* These 3 functions must be provided by the user. asn1_malloc()
   should return a value different from NULL when size = 0. */
void *asn1_malloc(size_t size);
void *asn1_realloc(void *ptr, size_t size);
void asn1_free(void *ptr);

void *asn1_mallocz(size_t size);
char *asn1_strdup(const char *str);
asn1_exception int __asn1_realloc_buf(uint8_t **pbuf, size_t elem_size,
                                      size_t *psize, size_t len, BOOL zero_init);
    
static inline asn1_exception int asn1_realloc_buf(uint8_t **pbuf,
                                                  size_t elem_size, 
                                                  size_t *psize, size_t len)
{
    if (len > *psize)
        return __asn1_realloc_buf(pbuf, elem_size, psize, len, FALSE);
    else
        return 0;
}

static inline asn1_exception int asn1_reallocz_buf(uint8_t **pbuf,
                                                   size_t elem_size, 
                                                   size_t *psize, size_t len)
{
    if (len > *psize)
        return __asn1_realloc_buf(pbuf, elem_size, psize, len, TRUE);
    else
        return 0;
}
    
/* Return the size (in bytes) of an ASN1 typed value or -1 if error
   (invalid type). */
asn1_ssize_t asn1_get_size(const ASN1CType *p);

/* Allocate a value of the ASN1 type 'p'. All fields are set to zero. */
void *asn1_mallocz_value(const ASN1CType *p);

/* Free a value of the ASN1 type 'p' */
void asn1_free_value(const ASN1CType *p, void *data);

/* Free all the values referenced by the structure 'data' but not data
   iteself. asn1_free_value(p, data) is equivalent to
   asn1_free_value_struct(p, data) followed by asn1_free(data). */
void asn1_free_value_struct(const ASN1CType *p, void *data);

/* Compare two ASN1 values of type 'p'. Return < 0 for less than, ==
   0 for equal, or > 0 for larger than. For composite values, a
   lexicographical ordering is assumed. */
int asn1_cmp_value(const ASN1CType *p, const void *data1,
                   const void *data2);

/* Copy 'data2' to 'data1' assuming 'data1' is allocated. All
   referenced data inside 'data1' is allocated. Return 0 if OK, < 0 if
   error. */
int asn1_copy_value(const ASN1CType *p, void *data1, const void *data2);

/* Clone the value 'data' of type 'p' (equivalent to
   asn1_mallocz_value() followed by asn1_copy_value()). Return NULL
   if error. */
void *asn1_clone_value(const ASN1CType *p, const void *data);

/* Generate a random ASN1 message of type 'p' (useful for
   testing). 'seed' is used to initialize the random generator */
void *asn1_random(const ASN1CType *p, int seed);

/* unaligned PER/aligned PER encode & decode */
asn1_ssize_t asn1_uper_encode(uint8_t **pbuf, const ASN1CType *p,
                              const void *data);
asn1_ssize_t asn1_aper_encode(uint8_t **pbuf, const ASN1CType *p,
                              const void *data);
asn1_ssize_t asn1_uper_encode2(uint8_t **pbuf, const ASN1CType *p,
                               const void *data, ASN1Error *err);
asn1_ssize_t asn1_aper_encode2(uint8_t **pbuf, const ASN1CType *p,
                               const void *data, ASN1Error *err);
asn1_ssize_t asn1_uper_decode(void **pdata, const ASN1CType *p,
                              const uint8_t *buf, size_t buf_len,
                              ASN1Error *err);
asn1_ssize_t asn1_aper_decode(void **pdata, const ASN1CType *p,
                              const uint8_t *buf, size_t buf_len,
                              ASN1Error *err);

/* BER encode & decode */
typedef struct {
    BOOL indefinite_len_for_constructed_encoding;
    int string_max_len; /* if larger, constructed encoding is used. 0
                           means no limit */
    BOOL use_sorted_set;
    BOOL use_sorted_set_of;
} ASN1BERParams;

asn1_ssize_t asn1_ber_encode(uint8_t **pbuf, const ASN1CType *p, 
                             const void *data, const ASN1BERParams *params);
asn1_ssize_t asn1_der_encode(uint8_t **pbuf, const ASN1CType *p, 
                             const void *data);
asn1_ssize_t asn1_ber_decode(void **pdata, const ASN1CType *p,
                             const uint8_t *buf, size_t buf_len, ASN1Error *err);

/* GSER encode & decode */

/* return < 0 if default action, otherwise the length of *pbuf
   allocated with asn1_malloc() which is output instead of the normal
   output */
typedef asn1_ssize_t ASN1OutputFilterFunc(void *filter_opaque, uint8_t **pbuf, 
                                          const ASN1CType *p, const void *data,
                                          int indent);
typedef struct {
    void *filter_opaque;
    ASN1OutputFilterFunc *filter_func; /* NULL if not needed */
    int indent; /* indentation level */
    /* don't dump bit strings as hexa when their size is a multiple of 4 */
    BOOL hex_bit_string_disabled;
} ASN1GSERParams;

asn1_ssize_t asn1_gser_encode(uint8_t **pbuf, const ASN1CType *p,
                              const void *data);
asn1_ssize_t asn1_gser_encode2(uint8_t **pbuf, const ASN1CType *p,
                               const void *data,
                               const ASN1GSERParams *params);
asn1_ssize_t asn1_gser_decode(void **pdata, const ASN1CType *p, const uint8_t *buf, 
                              size_t buf_len, ASN1Error *err);

/* XER encode & decode */
typedef struct {
    BOOL add_indentation;
    BOOL use_empty_tags;
    BOOL use_boolean_content; /* encode boolean type with content
                                 instead of empty tag */
    BOOL use_enumerated_content; /* encode enumerated type with
                                    content instead of empty tag */
    void *filter_opaque;
    ASN1OutputFilterFunc *filter_func; /* NULL if not needed */
    int indent; /* indentation level */
} ASN1XERParams;

asn1_ssize_t asn1_xer_encode(uint8_t **pbuf, const ASN1CType *p, const void *data);
asn1_ssize_t asn1_xer_encode2(uint8_t **pbuf, const ASN1CType *p, const void *data,
                          const ASN1XERParams *params);
asn1_ssize_t asn1_xer_decode(void **pdata, const ASN1CType *p, const uint8_t *buf, 
                         size_t buf_len, ASN1Error *err);

/* OER encode & decode */
asn1_ssize_t asn1_oer_encode(uint8_t **pbuf, const ASN1CType *p, const void *data);
asn1_ssize_t asn1_oer_encode2(uint8_t **pbuf, const ASN1CType *p,
                              const void *data, ASN1Error *err);
asn1_ssize_t asn1_oer_decode(void **pdata, const ASN1CType *p,
                             const uint8_t *buf, size_t buf_len, ASN1Error *err);

/* JER encoder & decode */
typedef struct {
    void *filter_opaque;
    ASN1OutputFilterFunc *filter_func; /* NULL if not needed */
    int indent; /* indentation level */
    int indent_width; /* number of spaces per indentation level. 0 =
                         no space in output */
} ASN1JERParams;

asn1_ssize_t asn1_jer_encode(uint8_t **pbuf, const ASN1CType *p,
                             const void *data);
asn1_ssize_t asn1_jer_encode2(uint8_t **pbuf, const ASN1CType *p,
                              const void *data, const ASN1JERParams *params);
asn1_ssize_t asn1_jer_decode(void **pdata, const ASN1CType *p,
                             const uint8_t *buf, size_t buf_len,
                             ASN1Error *err);

/* Return TRUE if the constraints are satisfied. Otherwise return
   FALSE and put an error message in 'err'. err = NULL is accepted. */
BOOL asn1_check_constraints(const ASN1CType *p, const void *data,
                            ASN1Error *err);

/* large integer functions */
void asn1_integer_init(ASN1Integer *r);
void asn1_integer_clear(ASN1Integer *r);
void asn1_integer_renorm(ASN1Integer *r);
asn1_exception int asn1_integer_resize(ASN1Integer *r, uint32_t len);
asn1_exception int asn1_integer_set(ASN1Integer *r, const ASN1Integer *a);
asn1_exception int asn1_integer_set_ui(ASN1Integer *r, uint32_t v);
asn1_exception int asn1_integer_set_ui64(ASN1Integer *r, uint64_t v);
asn1_exception int asn1_integer_set_si(ASN1Integer *r, int32_t v);
asn1_exception int asn1_integer_set_si64(ASN1Integer *r, int64_t v);
int asn1_integer_get_si_ov(const ASN1Integer *r, int *pval);
int asn1_integer_get_si64_ov(const ASN1Integer *r, int64_t *pval);
int asn1_integer_cmp(const ASN1Integer *a, const ASN1Integer *b);
int asn1_integer_cmp_si(const ASN1Integer *a, int32_t b);
asn1_exception int asn1_integer_add_internal(ASN1Integer *r, const ASN1Integer *a, const ASN1Integer *b, int b_neg);

static inline asn1_exception int asn1_integer_add(ASN1Integer *r, const ASN1Integer *a, const ASN1Integer *b)
{
    return asn1_integer_add_internal(r, a, b, 0);
}

static inline asn1_exception int asn1_integer_sub(ASN1Integer *r, const ASN1Integer *a, const ASN1Integer *b)
{
    return asn1_integer_add_internal(r, a, b, 1);
}
asn1_exception int asn1_integer_from_str(ASN1Integer *r, char **pp);
char *asn1_integer_to_str(const ASN1Integer *r, char **pbuf, int *plen);
asn1_exception int asn1_integer_out_str(FILE *f, const ASN1Integer *r);
int asn1_integer_get_bit_size(const ASN1Integer *r);
asn1_exception int asn1_integer_get_bit_size_2comp(int *pnb_bits,
                                                   const ASN1Integer *a);
asn1_exception int asn1_integer_from_2comp(ASN1Integer *r);
ASN1Integer *asn1_integer_to_2comp(ASN1Integer *tmp, const ASN1Integer *r,
                                   int *pnb_bits);

extern const char *asn1_ctype_names[ASN1_CTYPE_COUNT];

const char *asn1_get_generic_type_name(const ASN1CType *p);
/* return NULL if no user type name */
const char *asn1_get_user_type_name(const ASN1CType *p);
/* return the generic type name if no user type name */
const char *asn1_get_type_name(const ASN1CType *p);
/* return the CONTAINING type for an OCTET STRING or BIT STRING */
const ASN1CType *asn1_get_containing_type(const ASN1CType *p);

int asn1_parse_object_identifier(ASN1String *str, const char *input,
                                 size_t input_len, BOOL is_relative);

BOOL asn1_bitstring_get(const ASN1BitString *pBS, int BSPos);
int asn1_bitstring_from_args(ASN1BitString *pBS, size_t n, /*int*/...);
int asn1_bitstring_from_list(ASN1BitString *pBS, int n, int *ap);
#ifdef  __cplusplus
}
#endif

#endif /* _ASN1_DEFS_H */
