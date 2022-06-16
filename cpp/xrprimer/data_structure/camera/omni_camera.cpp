
#include "json_helper_internal.h"
#include <data_structure/camera/omni_camera.h>
#include <iostream>

OmniCameraParameter::OmniCameraParameter()
    : BaseCameraParameter(), k1_(0), k2_(0), k3_(0), k4_(0), k5_(0), k6_(0),
      p1_(0), p2_(0), xi_(0) {
    D_.setZero();
}

std::string OmniCameraParameter::ClassName() const {
    return "OmniCameraParameter";
}

bool OmniCameraParameter::SaveFile(const std::string &filename) const {
    Json::Value obj;

    SaveBaseCameraParameter(obj, *this);
    obj["k1"] = k1_;
    obj["k2"] = k2_;
    obj["k3"] = k3_;
    obj["k4"] = k4_;
    obj["k5"] = k5_;
    obj["k6"] = k6_;
    obj["p1"] = p1_;
    obj["p2"] = p2_;
    obj["xi"] = xi_;
    SaveMatrixToJson(obj, "D", D_);

    return JsonToFile(obj, filename);
}

bool OmniCameraParameter::LoadFile(const std::string &filename) {
    Json::Value obj;

    if (JsonFromFile(obj, filename)) {
        LoadBaseCameraParameter(obj, *this);
        k1_ = obj["k1"].asFloat();
        k2_ = obj["k2"].asFloat();
        k3_ = obj["k3"].asFloat();
        k4_ = obj["k4"].asFloat();
        k5_ = obj["k5"].asFloat();
        k6_ = obj["k6"].asFloat();
        p1_ = obj["p1"].asFloat();
        p2_ = obj["p2"].asFloat();
        xi_ = obj["xi"].asFloat();
        LoadMatrixFromJson(obj, "D", D_);
    }
    return false;
}