/* -*- Mode: C; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 8 -*-
 *
 * Copyright (C) 2011 Richard Hughes <richard@hughsie.com>
 *
 * Licensed under the GNU General Public License Version 2
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#pragma once

#include <glib-object.h>

#include <NetworkManager.h>
#include "net-object.h"

G_BEGIN_DECLS

#define NET_TYPE_DEVICE          (net_device_get_type ())

G_DECLARE_DERIVABLE_TYPE (NetDevice, net_device, NET, DEVICE, NetObject)

struct _NetDeviceClass
{
        NetObjectClass               parent_class;

        NMConnection * (*get_find_connection) (NetDevice *device);
};

NetDevice       *net_device_new                         (void);
NMDevice        *net_device_get_nm_device               (NetDevice      *device);
NMConnection    *net_device_get_find_connection         (NetDevice      *device);

GSList          *net_device_get_valid_connections       (NetDevice      *device);

G_END_DECLS
