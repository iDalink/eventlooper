# eventlooper

标准 Readme 样式

It`s a simple message driven looper which is used embeded project usually.

## `el_event`

`el_event` generated in runtime represent a `message` or `signal` in other design. Several field in its structure payload user-define data.

## `el_looper`

`el_event` is post to `el_looper`, and queued in fifo mode. Events will be excuted in order.

Invoker can check or cancel post in anytime.

## `el_timer`

It post `timer` message in `el_looper`. It`s safe to cancel or re-send.

## Port to system

In default, current version get complete `posix` and `esp32` backend.

Function defined `el_port.h` should be implemented in new platform.


Line 3 in `el_port.h` must be modified in specific platform by hand. **Do`nt forget!**
```C
#ifndef __EL_PORT_H__
#define __EL_PORT_H__
#include "el_port_posix.h"

void *el_mem_malloc(int size);
void *el_mem_malloc_from_spiram(int size);
void *el_mem_realloc(void *ptr, int size);

```
<center>▲ el_port.h<center>