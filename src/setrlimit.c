#include <sys/resource.h>

#include <Rdefines.h>

SEXP
R_getStackLimit()
{
    struct rlimit rlp;
    int status;
    status = getrlimit(RLIMIT_STACK, &rlp);
    if(status) {
	PROBLEM "getrlimit failed %d", status
	    ERROR;
    }    
    SEXP ans = NEW_INTEGER(2);
    INTEGER(ans)[0] =  rlp.rlim_cur;
    INTEGER(ans)[1] =  rlp.rlim_max;
    return(ans);
}


SEXP
R_setStackLimit(SEXP val)
{
    struct rlimit rlp = {0,0};
    int status;
    getrlimit(RLIMIT_STACK, &rlp);    
    rlp.rlim_cur = INTEGER(val)[0];
    status = setrlimit(RLIMIT_STACK, &rlp);
    if(status) {
	PROBLEM "setrlimit failed %d", status // , errno
	    ERROR;
    }
    return(R_NilValue);
}


#if 1

int
tmpmain(int argc, char *argv[])
{
    struct rlimit rlp;
    int status;
    getrlimit(RLIMIT_STACK, &rlp);
fprintf(stderr, "cur = %llu, max = %llu\n", rlp.rlim_cur, rlp.rlim_max);
    rlp.rlim_cur *= 2;
    status = setrlimit(RLIMIT_STACK, &rlp);
    fprintf(stderr, "%d: cur = %llu, max = %llu\n", status, rlp.rlim_cur, rlp.rlim_max);
    getrlimit(RLIMIT_STACK, &rlp);
    fprintf(stderr, "cur = %llu, max = %llu\n", rlp.rlim_cur, rlp.rlim_max);
    return(0);
}

void
Rmain()
{
    tmpmain(0, NULL);
}

#endif
