#ifndef __IO_H
#define __IO_H

#include "userInfo.h"

#include "admin.h"

void write_user(llist_head *user);

void read_user(llist_head *user);

void write_admin(admin_head *admin);

void read_admin(admin_head *admin);

#endif
