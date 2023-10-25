-- ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
-- ┃ Copyright: (c) 2023, Mike 'PhiSyX' S. (https://github.com/PhiSyX)         ┃
-- ┃ SPDX-License-Identifier: MPL-2.0                                          ┃
-- ┃ ╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌ ┃
-- ┃                                                                           ┃
-- ┃  This Source Code Form is subject to the terms of the Mozilla Public      ┃
-- ┃  License, v. 2.0. If a copy of the MPL was not distributed with this      ┃
-- ┃  file, You can obtain one at https://mozilla.org/MPL/2.0/.                ┃
-- ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

add_rules("mode.debug", "mode.release")

set_languages("c++17")

target("lexa-parser")
    set_kind("static")
    add_includedirs("include")
    add_files("src/**.cpp")
