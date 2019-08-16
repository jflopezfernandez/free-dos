
#include <string.h>

/** This is the canonical strlen function found in the C standard library. It
 *  will eventually be moved to the libc module, but as it is immediately
 *  necessary it is being written here now.
 * 
 */
size_t strlen(const char* str) {
    /** This variable is used as an accumulator as we iterate through the input
     *  string. On each iteration of the 'while' loop, we dereference the
     *  'str' pointer and then perform post-incrementation. The dereference will
     *  be true for every character of the input string until and excluding the
     *  null-terminator, at which point the 'while' loop will cease to evaluate
     *  to true and we return from the function. Since the null-terminator
     *  results in a false evaluation and therefore does not trigger the 'while'
     *  loop body, this is why strlen returns the length of the string
     *  *excluding* the null-terminator.
     * 
     */
    size_t length = 0;

    while (*str++)
        ++length;
    
    return length;
}
