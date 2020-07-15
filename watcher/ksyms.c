/*
 *  kEIPM (kerenl ELF Integrity Protection Module)
 *  Copyright (C) 2020 cassuto <diyer175@hotmail.com> & KingOfSmail
 * 
 *  This project is free edition; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public             
 *  License(GPL) as published by the Free Software Foundation; either      
 *  version 2.1 of the License, or (at your option) any later version.     
 *                                                                         
 *  This project is distributed in the hope that it will be useful,        
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of         
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU      
 *  Lesser General Public License for more details.                        
 */
#include <linux/kallsyms.h>
#include <linux/string.h>
#include "ksyms.h"

struct opaque {
    const char *name;
    long addr;
};

static int kallsyms_on_symbol(void *data, const char *name, void *module, long addr)
{
    struct opaque *target = (struct opaque *)data;
    if (addr && !module) { /* don't find in modules */
        if (0==strcmp(target->name, name)) {
            target->addr = addr;
            return 1;
        }
    }
    return 0;
}

void *find_kernel_entry(const char *symbol)
{
    struct opaque data = {symbol, 0};
	kallsyms_on_each_symbol((void *)kallsyms_on_symbol, &data);
	return (void *)data.addr;
}
