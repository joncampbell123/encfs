/*****************************************************************************
 * Author:   Valient Gough <vgough@pobox.com>
 *
 *****************************************************************************
 * Copyright (c) 2004, Valient Gough
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License
 * for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _BlockNameIO_incl_
#define _BlockNameIO_incl_

#include <stdint.h>
#include <memory>

#include "CipherKey.h"
#include "Interface.h"
#include "NameIO.h"
#include "shared_ptr.h"

class Cipher;

/*
    Implement NameIO interface for filename encoding.  Uses cipher in block
    mode to encode filenames.  The filenames are padded to be a multiple of the
    cipher block size.
*/
class BlockNameIO : public NameIO {
 public:
  static rel::Interface CurrentInterface(bool caseInsensitive = false);

  BlockNameIO(const rel::Interface &iface, const shared_ptr<Cipher> &cipher,
              const CipherKey &key, int blockSize,
              bool caseInsensitiveEncoding = false);
  virtual ~BlockNameIO();

  virtual rel::Interface interface() const;

  virtual int maxEncodedNameLen(int plaintextNameLen) const;
  virtual int maxDecodedNameLen(int encodedNameLen) const;

  // hack to help with static builds
  static bool Enabled();

 protected:
  virtual int encodeName(const char *plaintextName, int length, uint64_t *iv,
                         char *encodedName, int bufferLength) const;
  virtual int decodeName(const char *encodedName, int length, uint64_t *iv,
                         char *plaintextName, int bufferLength) const;

 private:
  int _interface;
  int _bs;
  shared_ptr<Cipher> _cipher;
  CipherKey _key;
  bool _caseInsensitive;
};

#endif
