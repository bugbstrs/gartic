#include "GarticException.h"
#include "CannotFetchQuoteException.h"

int main()
{
    GarticException<CannotFetchQuoteException> x;

    return 0;
}