//
// Created by lby on 25-5-18.
//

#ifndef EXAMPLE_PLUGIN_H
#define EXAMPLE_PLUGIN_H
#include "plugin_interface.h"

class ExamplePlugin final : public message_analyzer::PluginInterface {
public:
    std::optional<message_analyzer::DataTypeInfo> getTypeInfo() const override;

    message_analyzer::ErrorInfo setMapData(const std::string &jsonStr) override;

    message_analyzer::PlaybackProcessResult
    setTopicTypeData(const std::map<message_analyzer::Topic, std::any> &params) override;

    message_analyzer::PlaybackProcessResult
    sendPlaybackData(const std::map<message_analyzer::Topic, std::any> &params) override;
};


#endif //EXAMPLE_PLUGIN_H
