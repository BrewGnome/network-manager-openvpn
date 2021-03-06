/* -*- Mode: C; tab-width: 4; indent-tabs-mode: t; c-basic-offset: 4 -*- */
/* NetworkManager -- Network link manager
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA.
 *
 * (C) Copyright 2016 Red Hat, Inc.
 */

#ifndef __NM_SHARED_UTILS_H__
#define __NM_SHARED_UTILS_H__

/*****************************************************************************/

extern const void *const _NM_PTRARRAY_EMPTY[1];

#define NM_PTRARRAY_EMPTY(type) ((type const*) _NM_PTRARRAY_EMPTY)

static inline void
_nm_utils_strbuf_init (char *buf, gsize len, char **p_buf_ptr, gsize *p_buf_len)
{
	NM_SET_OUT (p_buf_len, len);
	NM_SET_OUT (p_buf_ptr, buf);
	buf[0] = '\0';
}

#define nm_utils_strbuf_init(buf, p_buf_ptr, p_buf_len) \
	G_STMT_START { \
		G_STATIC_ASSERT (G_N_ELEMENTS (buf) == sizeof (buf) && sizeof (buf) > sizeof (char *)); \
		_nm_utils_strbuf_init ((buf), sizeof (buf), (p_buf_ptr), (p_buf_len)); \
	} G_STMT_END
void nm_utils_strbuf_append (char **buf, gsize *len, const char *format, ...) _nm_printf (3, 4);
void nm_utils_strbuf_append_c (char **buf, gsize *len, char c);
void nm_utils_strbuf_append_str (char **buf, gsize *len, const char *str);

/*****************************************************************************/

gssize nm_utils_strv_find_first (char **list, gssize len, const char *needle);

char **_nm_utils_strv_cleanup (char **strv,
                               gboolean strip_whitespace,
                               gboolean skip_empty,
                               gboolean skip_repeated);

/*****************************************************************************/

gint64 _nm_utils_ascii_str_to_int64 (const char *str, guint base, gint64 min, gint64 max, gint64 fallback);

gint _nm_utils_ascii_str_to_bool (const char *str,
                                  gint default_value);

/*****************************************************************************/

/**
 * NMUtilsError:
 * @NM_UTILS_ERROR_UNKNOWN: unknown or unclassified error
 * @NM_UTILS_ERROR_CANCELLED_DISPOSING: when disposing an object that has
 *   pending aynchronous operations, the operation is cancelled with this
 *   error reason. Depending on the usage, this might indicate a bug because
 *   usually the target object should stay alive as long as there are pending
 *   operations.
 * @NM_UTILS_ERROR_INVALID_ARGUMENT: invalid argument.
 */
typedef enum {
	NM_UTILS_ERROR_UNKNOWN = 0,                 /*< nick=Unknown >*/
	NM_UTILS_ERROR_CANCELLED_DISPOSING,         /*< nick=CancelledDisposing >*/
	NM_UTILS_ERROR_INVALID_ARGUMENT,            /*< nick=InvalidArgument >*/
} NMUtilsError;

#define NM_UTILS_ERROR (nm_utils_error_quark ())
GQuark nm_utils_error_quark (void);

void nm_utils_error_set_cancelled (GError **error,
                                   gboolean is_disposing,
                                   const char *instance_name);
gboolean nm_utils_error_is_cancelled (GError *error,
                                      gboolean consider_is_disposing);

/*****************************************************************************/

gboolean nm_g_object_set_property (GObject *object,
                                   const gchar  *property_name,
                                   const GValue *value,
                                   GError **error);

/*****************************************************************************/

typedef enum {
	NM_UTILS_STR_UTF8_SAFE_FLAG_NONE                = 0,
	NM_UTILS_STR_UTF8_SAFE_FLAG_ESCAPE_CTRL         = 0x0001,
	NM_UTILS_STR_UTF8_SAFE_FLAG_ESCAPE_NON_ASCII    = 0x0002,
} NMUtilsStrUtf8SafeFlags;

const char *nm_utils_str_utf8safe_escape   (const char *str, NMUtilsStrUtf8SafeFlags flags, char **to_free);
const char *nm_utils_str_utf8safe_unescape (const char *str, char **to_free);

char *nm_utils_str_utf8safe_escape_cp   (const char *str, NMUtilsStrUtf8SafeFlags flags);
char *nm_utils_str_utf8safe_unescape_cp (const char *str);

char *nm_utils_str_utf8safe_escape_take (char *str, NMUtilsStrUtf8SafeFlags flags);

/*****************************************************************************/

#endif /* __NM_SHARED_UTILS_H__ */
