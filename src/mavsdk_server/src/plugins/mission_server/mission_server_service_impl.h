// WARNING: THIS FILE IS AUTOGENERATED! As such, it should not be edited.
// Edits need to be made to the proto files
// (see
// https://github.com/mavlink/MAVSDK-Proto/blob/master/protos/mission_server/mission_server.proto)

#include "mission_server/mission_server.grpc.pb.h"
#include "plugins/mission_server/mission_server.h"

#include "mavsdk.h"
#include "lazy_plugin.h"
#include "log.h"
#include <atomic>
#include <cmath>
#include <future>
#include <limits>
#include <memory>
#include <sstream>
#include <vector>

namespace mavsdk {
namespace mavsdk_server {

template<typename MissionServer = MissionServer, typename LazyPlugin = LazyPlugin<MissionServer>>
class MissionServerServiceImpl final : public rpc::mission_server::MissionServerService::Service {
public:
    MissionServerServiceImpl(LazyPlugin& lazy_plugin) : _lazy_plugin(lazy_plugin) {}

    template<typename ResponseType>
    void fillResponseWithResult(ResponseType* response, mavsdk::MissionServer::Result& result) const
    {
        auto rpc_result = translateToRpcResult(result);

        auto* rpc_mission_server_result = new rpc::mission_server::MissionServerResult();
        rpc_mission_server_result->set_result(rpc_result);
        std::stringstream ss;
        ss << result;
        rpc_mission_server_result->set_result_str(ss.str());

        response->set_allocated_mission_server_result(rpc_mission_server_result);
    }

    static std::unique_ptr<rpc::mission_server::MissionItem>
    translateToRpcMissionItem(const mavsdk::MissionServer::MissionItem& mission_item)
    {
        auto rpc_obj = std::make_unique<rpc::mission_server::MissionItem>();

        rpc_obj->set_seq(mission_item.seq);

        rpc_obj->set_frame(mission_item.frame);

        rpc_obj->set_command(mission_item.command);

        rpc_obj->set_current(mission_item.current);

        rpc_obj->set_autocontinue(mission_item.autocontinue);

        rpc_obj->set_param1(mission_item.param1);

        rpc_obj->set_param2(mission_item.param2);

        rpc_obj->set_param3(mission_item.param3);

        rpc_obj->set_param4(mission_item.param4);

        rpc_obj->set_x(mission_item.x);

        rpc_obj->set_y(mission_item.y);

        rpc_obj->set_z(mission_item.z);

        rpc_obj->set_mission_type(mission_item.mission_type);

        return rpc_obj;
    }

    static mavsdk::MissionServer::MissionItem
    translateFromRpcMissionItem(const rpc::mission_server::MissionItem& mission_item)
    {
        mavsdk::MissionServer::MissionItem obj;

        obj.seq = mission_item.seq();

        obj.frame = mission_item.frame();

        obj.command = mission_item.command();

        obj.current = mission_item.current();

        obj.autocontinue = mission_item.autocontinue();

        obj.param1 = mission_item.param1();

        obj.param2 = mission_item.param2();

        obj.param3 = mission_item.param3();

        obj.param4 = mission_item.param4();

        obj.x = mission_item.x();

        obj.y = mission_item.y();

        obj.z = mission_item.z();

        obj.mission_type = mission_item.mission_type();

        return obj;
    }

    static std::unique_ptr<rpc::mission_server::MissionPlan>
    translateToRpcMissionPlan(const mavsdk::MissionServer::MissionPlan& mission_plan)
    {
        auto rpc_obj = std::make_unique<rpc::mission_server::MissionPlan>();

        for (const auto& elem : mission_plan.mission_items) {
            auto* ptr = rpc_obj->add_mission_items();
            ptr->CopyFrom(*translateToRpcMissionItem(elem).release());
        }

        return rpc_obj;
    }

    static mavsdk::MissionServer::MissionPlan
    translateFromRpcMissionPlan(const rpc::mission_server::MissionPlan& mission_plan)
    {
        mavsdk::MissionServer::MissionPlan obj;

        for (const auto& elem : mission_plan.mission_items()) {
            obj.mission_items.push_back(translateFromRpcMissionItem(
                static_cast<mavsdk::rpc::mission_server::MissionItem>(elem)));
        }

        return obj;
    }

    static std::unique_ptr<rpc::mission_server::MissionProgress>
    translateToRpcMissionProgress(const mavsdk::MissionServer::MissionProgress& mission_progress)
    {
        auto rpc_obj = std::make_unique<rpc::mission_server::MissionProgress>();

        rpc_obj->set_current(mission_progress.current);

        rpc_obj->set_total(mission_progress.total);

        return rpc_obj;
    }

    static mavsdk::MissionServer::MissionProgress
    translateFromRpcMissionProgress(const rpc::mission_server::MissionProgress& mission_progress)
    {
        mavsdk::MissionServer::MissionProgress obj;

        obj.current = mission_progress.current();

        obj.total = mission_progress.total();

        return obj;
    }

    static rpc::mission_server::MissionResult::Result
    translateToRpcResult(const mavsdk::MissionServer::Result& result)
    {
        switch (result) {
            default:
                LogErr() << "Unknown result enum value: " << static_cast<int>(result);
            // FALLTHROUGH
            case mavsdk::MissionServer::Result::Unknown:
                return rpc::mission_server::MissionResult_Result_RESULT_UNKNOWN;
            case mavsdk::MissionServer::Result::Success:
                return rpc::mission_server::MissionResult_Result_RESULT_SUCCESS;
            case mavsdk::MissionServer::Result::Error:
                return rpc::mission_server::MissionResult_Result_RESULT_ERROR;
            case mavsdk::MissionServer::Result::TooManyMissionItems:
                return rpc::mission_server::MissionResult_Result_RESULT_TOO_MANY_MISSION_ITEMS;
            case mavsdk::MissionServer::Result::Busy:
                return rpc::mission_server::MissionResult_Result_RESULT_BUSY;
            case mavsdk::MissionServer::Result::Timeout:
                return rpc::mission_server::MissionResult_Result_RESULT_TIMEOUT;
            case mavsdk::MissionServer::Result::InvalidArgument:
                return rpc::mission_server::MissionResult_Result_RESULT_INVALID_ARGUMENT;
            case mavsdk::MissionServer::Result::Unsupported:
                return rpc::mission_server::MissionResult_Result_RESULT_UNSUPPORTED;
            case mavsdk::MissionServer::Result::NoMissionAvailable:
                return rpc::mission_server::MissionResult_Result_RESULT_NO_MISSION_AVAILABLE;
            case mavsdk::MissionServer::Result::UnsupportedMissionCmd:
                return rpc::mission_server::MissionResult_Result_RESULT_UNSUPPORTED_MISSION_CMD;
            case mavsdk::MissionServer::Result::TransferCancelled:
                return rpc::mission_server::MissionResult_Result_RESULT_TRANSFER_CANCELLED;
            case mavsdk::MissionServer::Result::NoSystem:
                return rpc::mission_server::MissionResult_Result_RESULT_NO_SYSTEM;
        }
    }

    static mavsdk::MissionServer::Result
    translateFromRpcResult(const rpc::mission_server::MissionResult::Result result)
    {
        switch (result) {
            default:
                LogErr() << "Unknown result enum value: " << static_cast<int>(result);
            // FALLTHROUGH
            case rpc::mission_server::MissionResult_Result_RESULT_UNKNOWN:
                return mavsdk::MissionServer::Result::Unknown;
            case rpc::mission_server::MissionResult_Result_RESULT_SUCCESS:
                return mavsdk::MissionServer::Result::Success;
            case rpc::mission_server::MissionResult_Result_RESULT_ERROR:
                return mavsdk::MissionServer::Result::Error;
            case rpc::mission_server::MissionResult_Result_RESULT_TOO_MANY_MISSION_ITEMS:
                return mavsdk::MissionServer::Result::TooManyMissionItems;
            case rpc::mission_server::MissionResult_Result_RESULT_BUSY:
                return mavsdk::MissionServer::Result::Busy;
            case rpc::mission_server::MissionResult_Result_RESULT_TIMEOUT:
                return mavsdk::MissionServer::Result::Timeout;
            case rpc::mission_server::MissionResult_Result_RESULT_INVALID_ARGUMENT:
                return mavsdk::MissionServer::Result::InvalidArgument;
            case rpc::mission_server::MissionResult_Result_RESULT_UNSUPPORTED:
                return mavsdk::MissionServer::Result::Unsupported;
            case rpc::mission_server::MissionResult_Result_RESULT_NO_MISSION_AVAILABLE:
                return mavsdk::MissionServer::Result::NoMissionAvailable;
            case rpc::mission_server::MissionResult_Result_RESULT_UNSUPPORTED_MISSION_CMD:
                return mavsdk::MissionServer::Result::UnsupportedMissionCmd;
            case rpc::mission_server::MissionResult_Result_RESULT_TRANSFER_CANCELLED:
                return mavsdk::MissionServer::Result::TransferCancelled;
            case rpc::mission_server::MissionResult_Result_RESULT_NO_SYSTEM:
                return mavsdk::MissionServer::Result::NoSystem;
        }
    }

    grpc::Status SubscribeIncomingMission(
        grpc::ServerContext* /* context */,
        const mavsdk::rpc::mission_server::SubscribeIncomingMissionRequest* /* request */,
        grpc::ServerWriter<rpc::mission_server::IncomingMissionResponse>* writer) override
    {
        if (_lazy_plugin.maybe_plugin() == nullptr) {
            rpc::mission_server::IncomingMissionResponse rpc_response;
            auto result = mavsdk::MissionServer::Result::NoSystem;
            fillResponseWithResult(&rpc_response, result);
            writer->Write(rpc_response);

            return grpc::Status::OK;
        }

        auto stream_closed_promise = std::make_shared<std::promise<void>>();
        auto stream_closed_future = stream_closed_promise->get_future();
        register_stream_stop_promise(stream_closed_promise);

        auto is_finished = std::make_shared<bool>(false);
        auto subscribe_mutex = std::make_shared<std::mutex>();

        _lazy_plugin.maybe_plugin()->subscribe_incoming_mission(
            [this, &writer, &stream_closed_promise, is_finished, subscribe_mutex](
                mavsdk::MissionServer::Result result,
                const mavsdk::MissionServer::MissionPlan incoming_mission) {
                rpc::mission_server::IncomingMissionResponse rpc_response;

                rpc_response.set_allocated_mission_plan(
                    translateToRpcMissionPlan(incoming_mission).release());

                auto rpc_result = translateToRpcResult(result);
                auto* rpc_mission_server_result = new rpc::mission_server::MissionServerResult();
                rpc_mission_server_result->set_result(rpc_result);
                std::stringstream ss;
                ss << result;
                rpc_mission_server_result->set_result_str(ss.str());
                rpc_response.set_allocated_mission_server_result(rpc_mission_server_result);

                std::unique_lock<std::mutex> lock(*subscribe_mutex);
                if (!*is_finished && !writer->Write(rpc_response)) {
                    _lazy_plugin.maybe_plugin()->subscribe_incoming_mission(nullptr);

                    *is_finished = true;
                    unregister_stream_stop_promise(stream_closed_promise);
                    stream_closed_promise->set_value();
                }
            });

        stream_closed_future.wait();
        std::unique_lock<std::mutex> lock(*subscribe_mutex);
        *is_finished = true;

        return grpc::Status::OK;
    }

    grpc::Status SubscribeCurrentItemChanged(
        grpc::ServerContext* /* context */,
        const mavsdk::rpc::mission_server::SubscribeCurrentItemChangedRequest* /* request */,
        grpc::ServerWriter<rpc::mission_server::CurrentItemChangedResponse>* writer) override
    {
        if (_lazy_plugin.maybe_plugin() == nullptr) {
            return grpc::Status::OK;
        }

        auto stream_closed_promise = std::make_shared<std::promise<void>>();
        auto stream_closed_future = stream_closed_promise->get_future();
        register_stream_stop_promise(stream_closed_promise);

        auto is_finished = std::make_shared<bool>(false);
        auto subscribe_mutex = std::make_shared<std::mutex>();

        _lazy_plugin.maybe_plugin()->subscribe_current_item_changed(
            [this, &writer, &stream_closed_promise, is_finished, subscribe_mutex](
                const mavsdk::MissionServer::MissionItem current_item_changed) {
                rpc::mission_server::CurrentItemChangedResponse rpc_response;

                rpc_response.set_allocated_mission_item(
                    translateToRpcMissionItem(current_item_changed).release());

                std::unique_lock<std::mutex> lock(*subscribe_mutex);
                if (!*is_finished && !writer->Write(rpc_response)) {
                    _lazy_plugin.maybe_plugin()->subscribe_current_item_changed(nullptr);

                    *is_finished = true;
                    unregister_stream_stop_promise(stream_closed_promise);
                    stream_closed_promise->set_value();
                }
            });

        stream_closed_future.wait();
        std::unique_lock<std::mutex> lock(*subscribe_mutex);
        *is_finished = true;

        return grpc::Status::OK;
    }

    grpc::Status SetCurrentItemComplete(
        grpc::ServerContext* /* context */,
        const rpc::mission_server::SetCurrentItemCompleteRequest* /* request */,
        rpc::mission_server::SetCurrentItemCompleteResponse* /* response */) override
    {
        if (_lazy_plugin.maybe_plugin() == nullptr) {
            return grpc::Status::OK;
        }

        _lazy_plugin.maybe_plugin()->set_current_item_complete();

        return grpc::Status::OK;
    }

    grpc::Status SubscribeClearAll(
        grpc::ServerContext* /* context */,
        const mavsdk::rpc::mission_server::SubscribeClearAllRequest* /* request */,
        grpc::ServerWriter<rpc::mission_server::ClearAllResponse>* writer) override
    {
        if (_lazy_plugin.maybe_plugin() == nullptr) {
            return grpc::Status::OK;
        }

        auto stream_closed_promise = std::make_shared<std::promise<void>>();
        auto stream_closed_future = stream_closed_promise->get_future();
        register_stream_stop_promise(stream_closed_promise);

        auto is_finished = std::make_shared<bool>(false);
        auto subscribe_mutex = std::make_shared<std::mutex>();

        _lazy_plugin.maybe_plugin()->subscribe_clear_all(
            [this, &writer, &stream_closed_promise, is_finished, subscribe_mutex](
                const uint32_t clear_all) {
                rpc::mission_server::ClearAllResponse rpc_response;

                rpc_response.set_clear_type(clear_all);

                std::unique_lock<std::mutex> lock(*subscribe_mutex);
                if (!*is_finished && !writer->Write(rpc_response)) {
                    _lazy_plugin.maybe_plugin()->subscribe_clear_all(nullptr);

                    *is_finished = true;
                    unregister_stream_stop_promise(stream_closed_promise);
                    stream_closed_promise->set_value();
                }
            });

        stream_closed_future.wait();
        std::unique_lock<std::mutex> lock(*subscribe_mutex);
        *is_finished = true;

        return grpc::Status::OK;
    }

    void stop()
    {
        _stopped.store(true);
        for (auto& prom : _stream_stop_promises) {
            if (auto handle = prom.lock()) {
                handle->set_value();
            }
        }
    }

private:
    void register_stream_stop_promise(std::weak_ptr<std::promise<void>> prom)
    {
        // If we have already stopped, set promise immediately and don't add it to list.
        if (_stopped.load()) {
            if (auto handle = prom.lock()) {
                handle->set_value();
            }
        } else {
            _stream_stop_promises.push_back(prom);
        }
    }

    void unregister_stream_stop_promise(std::shared_ptr<std::promise<void>> prom)
    {
        for (auto it = _stream_stop_promises.begin(); it != _stream_stop_promises.end();
             /* ++it */) {
            if (it->lock() == prom) {
                it = _stream_stop_promises.erase(it);
            } else {
                ++it;
            }
        }
    }

    LazyPlugin& _lazy_plugin;
    std::atomic<bool> _stopped{false};
    std::vector<std::weak_ptr<std::promise<void>>> _stream_stop_promises{};
};

} // namespace mavsdk_server
} // namespace mavsdk