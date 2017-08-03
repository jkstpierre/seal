#ifndef _SEAL_128_H_
#define _SEAL_128_H_

/*
	Simple Encryption ALgorithm (SEAL)
    Author: Joseph St. Pierre

    The Simple Encryption ALgorithm (SEAL) is a symmetric key block cipher that
    securely permutes a 128 bit block against a 128 bit key at a rate of 45+ MB/s making it suitable
    for encrypting large amounts of data fairly quickly without any hardware acceleration.

    NOTE: As of now the algorithm is undergoing academic review and as such should NOT be implemented for professional use until
        the review process concludes that SEAL is in fact usable for such purposes. In its current form, the algorithm should only
        be used for educational purposes.

        If any potential vulnerabilites to the cipher design are discovered during its review process, they will be corrected and
        the implementation described here will be updated accordingly.

    CONTACT:
        Author: Joseph St. Pierre
        Email: jkstpierre@wpi.edu

    Please email me if you discover any potential exploits!

    The author claims no responsibility for any and all damages that arise from the usage of this software. If you use
    SEAL in its current state to protect sensitive data in contradiction of the author's express warning: YOU DO SO AT YOUR
    OWN RISK!

    Once the review process is concluded, you are free to use SEAL
    for any commercial applications provided that you give credit to the author, and that the algorithm is only used as
    an auxiliary within a greater project and is not the main selling point of the application.

    Released: August 2017
*/

/*
    Copyright © 2017 Joseph St. Pierre

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <inttypes.h>
#include <stdlib.h>

/*
    The number of rounds for encryption.

    NOTE:
        Eight is the default number of rounds as it offers a good balance between security and speed. It is not recommended to
        perform less than eight rounds of SEAL since the security of the cipher begins to degrade.

        Due to the cipher's construction, it is recommended that the number of rounds be a multiple of four in order to remove
        any bias from the key bits (i.e. Certain portions of the key will be used less than other parts if the number of rounds
        is not a multiple of four).
*/
#define ROUND_COUNT (8)

/*
	Encrypt 128 bit block using SEAL:
		Permutes the block against the provided key using the Simple Encryption ALgorithm.

		After encryption, block will contain the cipher text.

        NOTE:
            SEAL assumes that both the block and the key are 128 bits long. If either the key or the block deviate
            from this assumed bit length, undefined behavior will occur!
*/
void seal_encrypt(uint32_t block[4], const uint32_t key[4]);

/*
	Decrypt 128 bit block using SEAL:
        Permutes the cipher-text block against the provided key using the Simple Encryption ALgorithm.

        After decryption, block will contain the plaintext.

        NOTE:
            SEAL assumes that both the block and the key are 128 bits long. If either the key or the block deviate
            from this assumed bit length, undefined behavior will occur!
*/
void seal_decrypt(uint32_t block[4], const uint32_t key[4]);

#endif

