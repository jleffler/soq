char const         *ccp   = 0;     /* OK */
char const * const *ccpcp = &ccp;  /* OK */
char       * const *cpcp  = &ccp;  /* X: OK  - actually BAD */
char const *       *ccpp  = &ccp;  /* X: BAD - actually OK  */

