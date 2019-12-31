/*
   Copyright (c) 2020, The LineageOS Project. All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are
   met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above
      copyright notice, this list of conditions and the following
      disclaimer in the documentation and/or other materials provided
      with the distribution.
    * Neither the name of The Linux Foundation nor the names of its
      contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
   WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
   ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
   BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
   BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
   WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
   OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
   IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */


#include <stdlib.h>

#include <android-base/file.h>
#include <android-base/logging.h>
#include <android-base/properties.h>
#include <android-base/strings.h>

#include "property_service.h"
#include "vendor_init.h"

#define _REALLY_INCLUDE_SYS__SYSTEM_PROPERTIES_H_
#include <sys/_system_properties.h>

using android::base::GetProperty;
using android::base::ReadFileToString;
using android::base::Trim;
using android::init::property_set;

#define SERIAL_NUMBER_FILE "/efs/FactoryApp/serial_no"

// copied from build/tools/releasetools/ota_from_target_files.py
// but with "." at the end and empty entry
std::vector<std::string> ro_product_props_default_source_order = {
    "",
    "product.",
    "product_services.",
    "odm.",
    "vendor.",
    "system.",
};

void property_override(char const prop[], char const value[], bool add = true)
{
    auto pi = (prop_info *) __system_property_find(prop);

    if (pi != nullptr) {
        __system_property_update(pi, value, strlen(value));
    } else if (add) {
        __system_property_add(prop, strlen(prop), value, strlen(value));
    }
}

void vendor_load_properties()
{
    const std::string bootloader = GetProperty("ro.bootloader", "");

    char const *serial_number_file = SERIAL_NUMBER_FILE;
    std::string serial_number;

    if (ReadFileToString(serial_number_file, &serial_number)) {
        serial_number = Trim(serial_number);
        property_override("ro.serialno", serial_number.c_str());
    }

    const auto set_ro_product_prop = [](const std::string &source,
            const std::string &prop, const std::string &value) {
        auto prop_name = "ro.product." + source + prop;
        property_override(prop_name.c_str(), value.c_str(), false);
    };

    if (bootloader.find("N915F") == 0) {
        /* tbltexx */
        for (const auto &source : ro_product_props_default_source_order) {
            set_ro_product_prop(source, "fingerprint", "samsung/tblte/tblte:6.0.1/MMB29M/N915FXXS1DQH2:user/release-keys");
            set_ro_product_prop(source, "device", "tblte");
            set_ro_product_prop(source, "model", "SM-N915F");
            set_ro_product_prop(source, "name", "tblte");
        }
        property_override("ro.build.description", "tblte-user 6.0.1 MMB29M N915FXXS1DQH2 release-keys");
        property_override("ro.build.product", "tblte");
    } else if (bootloader.find("N915FY") == 0) {
        /* tbltexx */
        for (const auto &source : ro_product_props_default_source_order) {
            set_ro_product_prop(source, "fingerprint", "samsung/tbltebtu/tblte:6.0.1/MMB29M/N915FYXXS1DQH2:user/release-keys");
            set_ro_product_prop(source, "device", "tblte");
            set_ro_product_prop(source, "model", "SM-N915FY");
            set_ro_product_prop(source, "name", "tbltebtu");
        }
        property_override("ro.build.description", "tbltebtu-user 6.0.1 MMB29M N915FYXXS1DQH2 release-keys");
        property_override("ro.build.product", "tblte");
    } else if (bootloader.find("N915G") == 0) {
        /* tbltedt */
        for (const auto &source : ro_product_props_default_source_order) {
            set_ro_product_prop(source, "fingerprint", "samsung/tbltedt/tblte:6.0.1/MMB29M/N915GDTS1DQE1:user/release-keys");
            set_ro_product_prop(source, "device", "tblte");
            set_ro_product_prop(source, "model", "SM-N915G");
            set_ro_product_prop(source, "name", "tbltedt");
        }
        property_override("ro.build.description", "tbltedt-user 6.0.1 MMB29M N915GDTS1DQE1 release-keys");
        property_override("ro.build.product", "tblte");
    } else if (bootloader.find("N915P") == 0) {
        /* tbltespr */
        for (const auto &source : ro_product_props_default_source_order) {
            set_ro_product_prop(source, "fingerprint", "samsung/tbltespr/tblte:6.0.1/MMB29M/N915PVPS4DQC1:user/release-keys");
            set_ro_product_prop(source, "device", "tbltespr");
            set_ro_product_prop(source, "model", "SM-N915P");
            set_ro_product_prop(source, "name", "tbltespr");
        }
        property_override("ro.build.description", "tbltespr-user 6.0.1 MMB29M N915PVPS4DQC1 release-keys");
        property_override("ro.build.product", "tbltespr");
        property_set("ro.cdma.home.operator.alpha", "Sprint");
        property_set("ro.cdma.home.operator.numeric", "310120");
    } else if (bootloader.find("N915R4") == 0) {
        /* tblteusc */
        for (const auto &source : ro_product_props_default_source_order) {
            set_ro_product_prop(source, "fingerprint", "samsung/tblteusc/tblte:6.0.1/MMB29M/N915R4TYS1CQC1:user/release-keys");
            set_ro_product_prop(source, "device", "tblteusc");
            set_ro_product_prop(source, "model", "SM-N915R4");
            set_ro_product_prop(source, "name", "tblteusc");
        }
        property_override("ro.build.description", "tblteusc-user 6.0.1 MMB29M N915R4TYS1CQC1 release-keys");
        property_override("ro.build.product", "tblteusc");
        property_set("ro.cdma.home.operator.alpha", "U.S. Cellular");
        property_set("ro.cdma.home.operator.numeric", "311580");
    } else if (bootloader.find("N915T") == 0) {
        /* tbltetmo */
        for (const auto &source : ro_product_props_default_source_order) {
            set_ro_product_prop(source, "fingerprint", "samsung/tbltetmo/tblte:6.0.1/MMB29M/N915TUVS2EQE2:user/release-keys");
            set_ro_product_prop(source, "device", "tbltetmo");
            set_ro_product_prop(source, "model", "SM-N915T");
            set_ro_product_prop(source, "name", "tbltetmo");
        }
        property_override("ro.build.description", "tbltetmo-user 6.0.1 MMB29M N915TUVS2EQE2 release-keys");
        property_override("ro.build.product", "tbltetmo");
    } else if (bootloader.find("N915V") == 0) {
        /* tbltevzw */
        for (const auto &source : ro_product_props_default_source_order) {
            set_ro_product_prop(source, "fingerprint", "Verizon/tbltevzw/tblte:6.0.1/MMB29M/N915VVRS2CQE1:user/release-keys");
            set_ro_product_prop(source, "device", "tbltevzw");
            set_ro_product_prop(source, "model", "SM-N915V");
            set_ro_product_prop(source, "name", "tbltevzw");
        }
        property_override("ro.build.description", "tbltevzw-user 6.0.1 MMB29M N915VVRS2CQE1 release-keys");
        property_override("ro.build.product", "tbltevzw");
        property_set("ro.cdma.home.operator.alpha", "Verizon");
        property_set("ro.cdma.home.operator.numeric", "311480");
    } else if (bootloader.find("N915W8") == 0) {
        /* tbltecan */
        for (const auto &source : ro_product_props_default_source_order) {
            set_ro_product_prop(source, "fingerprint", "samsung/tbltecan/tblte:6.0.1/MMB29M/N915W8VLS1DQD1:user/release-keys");
            set_ro_product_prop(source, "device", "tbltecan");
            set_ro_product_prop(source, "model", "SM-N915W8");
            set_ro_product_prop(source, "name", "tbltecan");
        }
        property_override("ro.build.description", "tbltecan-user 6.0.1 MMB29M N915W8VLS1DQD1 release-keys");
        property_override("ro.build.product", "tbltecan");
    }

    const std::string device = GetProperty("ro.product.device", "");
    LOG(INFO) << "Found bootloader " << bootloader << ". " << "Setting build properties for " << device << ".\n";
}
