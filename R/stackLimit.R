stackLimit =
function(val = integer())
{
    if(length(val) == 0)
        .Call("R_getStackLimit")
    else
        .Call("R_setStackLimit", as.integer(val))
}
