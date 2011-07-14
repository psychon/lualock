#include <X11/Xlib.h>
#include <X11/X.h>
#include <X11/extensions/dpms.h>
#include <lauxlib.h>

#include "clib/dpms.h"

int lualock_lua_dpms_set(lua_State *L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    lua_getfield(L, 1, "standby");
    lua_getfield(L, 1, "suspend");
    lua_getfield(L, 1, "off");
    
    Display *dpy = XOpenDisplay(NULL);
    XSynchronize(dpy, True);
    if (DPMSCapable(dpy))
        printf("%i", DPMSSetTimeouts(dpy, luaL_checkint(L, 2), luaL_checkint(L, 3),
                        luaL_checkint(L, 4)));
    DPMSEnable(dpy);
    return 0;
}

void lualock_lua_dpms_init(lua_State *L) {
    lua_register(L, "dpms", lualock_lua_dpms_set);
}
