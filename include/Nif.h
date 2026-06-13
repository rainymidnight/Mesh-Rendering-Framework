#pragma once

class Nif {
    Nif() {}

public:
    RE::NiPointer<RE::NiNode> node;
    RE::NiAVObject* obj;
    RE::NiPoint3 rotation;
    std::string nifPath;
    static Nif* Create(const char* nifPath, bool applyInvMarker) {
        RE::BSModelDB::DBTraits::ArgsType args;
        RE::NiPointer<RE::NiNode> tmp;

        auto error = RE::BSModelDB::Demand(nifPath, tmp, args);
        if (error != RE::BSResource::ErrorCode::kNone || !tmp.get()) {
            logger::error("Failed to load XpMarkerNif! Error code: {}", (int)error);
            return nullptr;
        }

        auto result = new Nif();
        result->nifPath = nifPath;

        result->obj = static_cast<RE::NiAVObject*>(tmp.get()->Clone());
        result->node.reset(result->obj->AsNode());
        result->obj->SetMotionType(RE::hkpMotion::MotionType::kKeyframed, true, false, true);

        if (applyInvMarker) {
            auto extraData = result->obj->GetExtraData("INV");
            if (extraData) {
                auto marker = reinterpret_cast<RE::BSInvMarker*>(extraData);
                result->rotation = marker->GetRotationEulerAnglesXYZ();
                result->obj->local.rotate.SetEulerAnglesXYZ(result->rotation.x, result->rotation.y, result->rotation.z);
            } 
        }

        return result;
    }
};