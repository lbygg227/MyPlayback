#pragma once
#include <string>
#include <vector>
#include <optional>
#include <any>
#include <map>
#include <memory>
#include <variant>

namespace message_analyzer {

  using MapType = std::string;
  using PlayBackTopic = std::string;
  using Topic = std::string;
  using PngType = std::string;
  using JsonType = std::string;

  enum class ErrorType : int8_t
  {
    kOk = 0,
    kError,
    kDBError,
    kGRPCError,
    kROSError
  };

  struct DataTypeInfo {
    std::vector<MapType> maps;
    std::vector<PlayBackTopic> playBacks;
    std::vector<Topic> topics;
  };

  struct ErrorInfo {
    int retCode;
    ErrorType errType;
    std::string errorMsg;

    ErrorInfo() :retCode(0), errType(ErrorType::kOk) {}

    ErrorInfo(const int& errCode, std::string errMsg, const ErrorType& errType)
      : retCode(errCode), errType(errType), errorMsg(std::move(errMsg)) {
    }

    [[nodiscard]] bool IsOk() const { return errType == ErrorType::kOk; }
  };

  using PlaybackProcessResult = std::variant<PngType, JsonType, ErrorInfo, std::monostate>;

  class PluginInterface {
  public:
    PluginInterface() {};

    virtual ~PluginInterface() {};

    PluginInterface(const PluginInterface&) = delete;

    PluginInterface& operator=(const PluginInterface&) = delete;

    // �ṩ�����ͼ����������ros msg��������
    virtual std::optional<DataTypeInfo> getTypeInfo() const = 0;
    // ��ȡ��ͼ���ݣ��ο�map-masterͨ�õ�ͼ���ݽӿ�
    virtual ErrorInfo setMapData(const std::string& jsonStr) = 0;
    // ��ȡbag��topic��ȫ�����ݣ����ؼ�������
    virtual PlaybackProcessResult setTopicTypeData(const std::map<Topic, std::any>& params) = 0;
    // ���ݻطŹ��̣���ȡ�طŹ����е�topic���ݣ���֡�������ؼ�������
    virtual PlaybackProcessResult sendPlaybackData(const std::map<Topic, std::any>& params) = 0;

  protected:
  };
}