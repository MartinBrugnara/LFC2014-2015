#include <stdio.h>
#include "calc.h"
#include "y.tab.h"
extern int flagSkip;
extern int insideLoop;

int ex(nodeType *p) {
    if (!p) return 0;
    if(flagSkip) return 0;
    switch(p->type) {
        case typeCon:       return p->con.value;
        case typeId:        return sym[p->id.i];
        case typeOpr:
            switch(p->opr.oper) {
                case WHILE:
                    while(ex(p->opr.op[0]))
                    {
                        ex(p->opr.op[1]);
                    }
                    return 0;
                case SKIP:
                    flagSkip = 1;
                    return  0;
                case FOR:
                    insideLoop++;
/*                    sym[p->opr.op[0]->id.i] = ex(p->opr.op[1]);
                    while(sym[p->opr.op[0]->id.i] - ex(p->opr.op[2])){
                        ex(p->opr.op[3]);
                        sym[p->opr.op[0]->id.i]++;
                    }
    don't buy this one
*/                  
                    for(sym[p->opr.op[0]->id.i] = ex(p->opr.op[1]); 
                        sym[p->opr.op[0]->id.i]< ex(p->opr.op[2]); 
                        sym[p->opr.op[0]->id.i]++){
                       ex(p->opr.op[3]);
                        flagSkip = 0;
                    }
                    insideLoop--;
                    return 0;
                case IF:
                    if (ex(p->opr.op[0])){
                        
                        ex(p->opr.op[1]);
                    }
                    else if (p->opr.nops > 2)
                    {
                        ex(p->opr.op[2]);
                    }
                    return 0;
                case PRINT:     printf("%d\n", ex(p->opr.op[0])); return 0;
                case ';':       ex(p->opr.op[0]); return ex(p->opr.op[1]);
                case '=':       return sym[p->opr.op[0]->id.i] = ex(p->opr.op[1]);
                case UMINUS:    return -ex(p->opr.op[0]);
                case '+':       return ex(p->opr.op[0]) + ex(p->opr.op[1]);
                case '-':       return ex(p->opr.op[0]) - ex(p->opr.op[1]);
                case '*':       return ex(p->opr.op[0]) * ex(p->opr.op[1]);
                case '/':       return ex(p->opr.op[0]) / ex(p->opr.op[1]);
                case '<':       return ex(p->opr.op[0]) < ex(p->opr.op[1]);
                case '>':       return ex(p->opr.op[0]) > ex(p->opr.op[1]);
                case GE:        return ex(p->opr.op[0]) >= ex(p->opr.op[1]);
                case LE:        return ex(p->opr.op[0]) <= ex(p->opr.op[1]);
                case NE:        return ex(p->opr.op[0]) != ex(p->opr.op[1]);
                case EQ:        return ex(p->opr.op[0]) == ex(p->opr.op[1]);
            }
    }
    return 0;
}