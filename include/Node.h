#pragma once

class Node {

public:
    RE::NiPointer<RE::NiNode> node;
    RE::NiAVObject* obj;
    Node() {
        RE::NiPointer<RE::NiNode> tmp;

        tmp.reset(RE::NiNode::Create());

        obj = static_cast<RE::NiAVObject*>(tmp.get()->Clone());
        node.reset(obj->AsNode());
        node->SetMotionType(RE::hkpMotion::MotionType::kKeyframed, true, false, true);
    }

    void Update(RE::NiMatrix3 angle, RE::NiPoint3 position, float scale) {
        node->local.rotate = angle;
        node->local.translate = position;
        node->local.scale = scale;
        UpdateDirty();
    }

    void Update() {
        RE::NiUpdateData udata;
        udata.time = 0.0f;
        udata.flags = RE::NiUpdateData::Flag::kNone;
        node->Update(udata);
    }

    void UpdateDirty() {
        RE::NiUpdateData udata;
        udata.flags = RE::NiUpdateData::Flag::kDirty;
        udata.time = (float)((*(long*)REL::RelocationID(523662, 410201).address())) * 0.001;
        node->Update(udata);
    }
};