/**
 * Copyright (c) 2013, Krzysztof Kliś <krzysztof.klis@gmail.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _CONTRACT_HPP
#define _CONTRACT_HPP

#include <exception>
#include <sstream>

namespace contract {
    class exception : public std::exception {
      private:
        std::string message;
      public:
        exception(const char* rule, const char *filename, int line) {
            std::stringstream ss;
            ss << "Rule '" << rule << "' violated at " << filename << ":" << line;
            message = ss.str();
        }
        virtual ~exception() throw () {
        }
        const char* what() const throw() {
            return message.c_str();
        }
    };

    void assures(bool condition, const char* rule, const char *filename, int line) {
        if (!condition) {
            throw exception(rule, filename, line);
        }
    }
};

#ifdef NDEBUG
#define ASSURES(condition) (void)0;
#else
#define ASSURES(condition) contract::assures(condition, #condition, __FILE__, __LINE__);
#endif

#define REQUIRES(condition) ASSURES(condition)
#define ENSURES(condition) ASSURES(condition)

#endif //_CONTRACT_HPP
