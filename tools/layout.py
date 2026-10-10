"""Module layout of MM3.EXE for the full relink (link order = list order).
ROOT: (module, segtable index) for root code segments; OVR: (module, stub segment) for VROOMM overlays.
DATA / BSS: DGROUP byte ranges [a, b) contributed as blob data by a module (blob or data-only module)."""

ROOT = [('main', 1), ('view', 2), ('events', 3), ('scene', 4), ('itemname', 5), ('stattext', 6), ('sys', 7),
        ('mazeio', 8), ('empty9', 9), ('snddrv', 10)]
OVR = [('init', 0x17f2), ('ending', 0x17fd), ('misc1', 0x1800), ('town', 0x1806), ('charinfo', 0x180c),
       ('cpanel', 0x1816), ('mazeload', 0x1821), ('guild', 0x182a), ('building', 0x1831), ('combat', 0x1839),
       ('spells', 0x1843), ('items', 0x1861), ('shop', 0x1867)]
RTL_DATA = 0x8724   # first DGROUP _DATA byte of the runtime library (C0M _DATA ends at 0xaa)
RTL_BSS = 0xf088
# _DATA owner = module whose OBJ holds those bytes (globals then pooled strings); C0M _DATA ends at 0xaa.
# main/init/mazeio ranges are exact (their C _DATA matches); view holds view..sys data, ending holds ending..shop data.
DATA = {'main': (0xaa, 0xf1b), 'gamedata': (0xf1c, 0x1e2e), 'init': (0x1e2e, 0x201b), 'mazeio': (0x8564, RTL_DATA)}
# exact _DATA start of each overlay after init (link order); None = not pinned yet: its data stays with the
# previous overlay's blob range (so a C overlay needs the NEXT one pinned too)
OVR_DATA = [('ending', 0x201c), ('misc1', 0x2600), ('town', 0x2744), ('charinfo', 0x29bc), ('cpanel', 0x308c),
            ('mazeload', 0x3692), ('guild', 0x3be6), ('building', 0x42e6), ('combat', 0x4b24), ('spells', 0x4bd8),
            ('items', 0x4e78), ('shop', 0x52d2)]
_k = [(n, a) for n, a in OVR_DATA if a is not None] + [(None, 0x8564)]
DATA.update({n: (a, b) for (n, a), (_, b) in zip(_k, _k[1:])})
BSS = {'gbss': (0x8d60, RTL_BSS)}   # game BSS (src/gbss.asm)
# data-only modules linked right after sys: gamedata = DGROUP f1c-1e2e (view..sys data), gbss = the game BSS
DATA_MODS = ['gamedata', 'gbss']

EXTRA_EXTS = {'main': ['__argv']}   # RTL data referenced only by DS offset (no reloc) but pulling a lib module


# RTL symbols the game defines itself (DGROUP addresses)
DATA_PUBS = {'__stklen': 0xe7f, '__ovrbuffer': 0xe81}


def extra_pubs(n):
    """publics (name, segname, DGROUP address) to add to module n"""
    out = []
    for p, a in DATA_PUBS.items():
        if n in DATA and DATA[n][0] <= a < DATA[n][1]: out.append((p, '_DATA', a))
    return out
