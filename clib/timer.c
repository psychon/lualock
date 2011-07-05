#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <stdlib.h>
#include <unistd.h>

#include "lualock.h"
#include "timer.h"

void timer_new(l_timer_t *timer, unsigned int int_us, int cycles, void (*cb)(void)) {
    timer->cycles = cycles;
    timer->completed_cycles = 0,
    timer->running = TRUE;
    timer->int_us = int_us;
    timer->cb = cb;
    timer_run(timer);
    int source_id = g_timeout_add(int_us / 1000.0, timer_run, timer);
}
    
gboolean timer_run(void *data) {
    l_timer_t *timer = (l_timer_t *)data;
    if (timer->cycles != 0 && timer->completed_cycles >= timer->cycles)
        return FALSE;
    else
        timer->cb();
    timer->completed_cycles++;
    return TRUE;
}

void timer_run_lua_function() {
    lua_getfield(lualock.L, LUA_REGISTRYINDEX, "callback");
    lua_pcall(lualock.L, 0, 0, 0);
}

static int lualock_lua_timer_new(lua_State *L) {
    l_timer_t *timer = lua_newuserdata(L, sizeof(l_timer_t));
    
    int interval = luaL_checknumber(L, 2) * 1000000;
    int run_times = lua_tonumber(L, 3);
    lua_pop(L, 2);
    lua_pushstring(L, "callback");
    lua_insert(L, 1);
    lua_settable(L, LUA_REGISTRYINDEX);
        
    timer_new(timer, interval, run_times, timer_run_lua_function);
    return 1;
}

void lualock_lua_timer_init(lua_State *L) {
        const struct luaL_reg lualock_timer_lib[] =
        {
                { "new", lualock_lua_timer_new },
                { NULL, NULL }
        };
        luaL_register(L, "timer", lualock_timer_lib);
}
