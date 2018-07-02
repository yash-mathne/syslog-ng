/*
 * Copyright (c) 2002-2018 Balabit
 * Copyright (c) 2018 Laszlo Budai <laszlo.budai@balabit.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * As an additional exemption you are allowed to compile & link against the
 * OpenSSL libraries as published by the OpenSSL project. See the file
 * COPYING for details.
 *
 */

#ifndef ATOMIC_GSSIZE_H_INCLUDED
#define ATOMIC_GSSIZE_H_INCLUDED

#include "syslog-ng.h"

typedef struct
{
  gssize value;
} atomic_gssize;

static inline void
atomic_gssize_add(atomic_gssize *a, gssize add)
{
  g_atomic_pointer_add(&a->value, add);
}

static inline void
atomic_gssize_sub(atomic_gssize *a, gssize sub)
{
  if (a)
    g_atomic_pointer_add(&a->value, -1 * sub);
}

static inline void
atomic_gssize_inc(atomic_gssize *a)
{
  if (a)
    g_atomic_pointer_add(&a->value, 1);
}

static inline void
atomic_gssize_dec(atomic_gssize *a)
{
  if (a)
    g_atomic_pointer_add(&a->value, -1);
}

static inline gssize
atomic_gssize_get(atomic_gssize *a)
{
  return (gssize)g_atomic_pointer_get(&a->value);
}

static inline void
atomic_gssize_set(atomic_gssize *a, gssize value)
{
  g_atomic_pointer_set(&a->value, value);
}

static inline gsize
atomic_gssize_get_unsigned(atomic_gssize *a)
{
  return (gsize)g_atomic_pointer_get(&a->value);
}

static inline gssize
atomic_gssize_racy_get(atomic_gssize *a)
{
  return a->value;
}

static inline gsize
atomic_gssize_racy_get_unsigned(atomic_gssize *a)
{
  return (gsize)a->value;
}

static inline void
atomic_gssize_racy_set(atomic_gssize *a, gssize value)
{
  a->value = value;
}

#endif
