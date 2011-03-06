/* Copyright (c) 1993, 2001 Joshua E. Barnes, Honolulu, HI.
   Copyright 2010 Matthew Arsenault, Travis Desell, Boleslaw
Szymanski, Heidi Newberg, Carlos Varela, Malik Magdon-Ismail and
Rensselaer Polytechnic Institute.

This file is part of Milkway@Home.

Milkyway@Home is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Milkyway@Home is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Milkyway@Home.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "milkyway_util.h"
#include "nbody_types.h"


int destroyNBodyCtx(NBodyCtx* ctx)
{
    if (ctx->outfile && ctx->outfile != DEFAULT_OUTPUT_FILE)
    {
        if (fclose(ctx->outfile))
        {
            perror("closing output\n");
            return TRUE;
        }
    }

    return FALSE;
}

static void freeTree(Tree* t)
{
    node* p;
    node* tmp;

    p = (node*) t->root;
    while (p != NULL)
    {
        if (isCell(p))
        {
            tmp = More(p);
            free(p);
            p = tmp;
        }
        else                        /* skip over bodies */
            p = Next(p);
    }

    t->root = NULL;
    t->cellused = 0;
}

static void freeFreeCells(node* freecell)
{
    node* p;
    node* tmp;

    p = freecell;
    while (p)
    {
        tmp = Next(p);
        free(p);
        p = tmp;
    }
}

void destroyNBodyState(NBodyState* st)
{
    freeTree(&st->tree);
    freeFreeCells(st->freecell);
    mwFreeA(st->bodytab);
    mwFreeA(st->acctab);

  #if NBODY_OPENCL
    cleanupNBodyCL(st);
  #endif /* NBODY_OPENCL */
}


