/*
 * The following code creates the lookup tables used to calculate the
 * FCS-16 for PPP in CPC/IP.  Code liberally borrowed from RFC1662 (C.1).
 *
 * This code is NOT copyright Mark RISON.
 */

/*
 * Generate a FCS-16 table.
 *
 * Drew D. Perkins at Carnegie Mellon University.
 *
 * Code liberally borrowed from Mohsen Banan and D. Hugh Redelmeier.
 */

/*
 * The FCS-16 generator polynomial: x**0 + x**5 + x**12 + x**16.
 */
#define P       0x8408


int main(void)
{
    register unsigned int b, v;
    register int i;
    unsigned int fcstab[256];

    for (b = 0; b < 256; ++b) {
        v = b;
        for (i = 8; i--; )
            v = v & 1 ? (v >> 1) ^ P : v >> 1;

        fcstab[b] = v & 0xffff;
    }
    printf(".pppfcstab16\n");
    printf("; pppfcstab16_lsb[256]");
    for (b = 0; ; ) {
        if (b % 8 == 0)
            printf("\ndefb\t");

        printf("&%02x", fcstab[b] & 0xff);
        if (++b == 256)
            break;

        if (b % 8 != 0)
            printf(", ");
    }
    printf("\n");
    printf("; pppfcstab16_msb[256]");
    for (b = 0; ; ) {
        if (b % 8 == 0)
            printf("\ndefb\t");

        printf("&%02x", fcstab[b] >> 8);
        if (++b == 256)
            break;

        if (b % 8 != 0)
            printf(", ");
    }
    printf("\n");

    return 0;
}
