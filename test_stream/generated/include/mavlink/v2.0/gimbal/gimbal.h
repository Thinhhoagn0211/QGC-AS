/** @file
 *  @brief MAVLink comm protocol generated from gimbal.xml
 *  @see http://mavlink.org
 */
#pragma once
#ifndef MAVLINK_GIMBAL_H
#define MAVLINK_GIMBAL_H

#ifndef MAVLINK_H
    #error Wrong include order: MAVLINK_GIMBAL.H MUST NOT BE DIRECTLY USED. Include mavlink.h from the same directory instead or set ALL AND EVERY defines from MAVLINK.H manually accordingly, including the #define MAVLINK_H call.
#endif

#define MAVLINK_GIMBAL_XML_HASH 1107590954653013793

#ifdef __cplusplus
extern "C" {
#endif

// MESSAGE LENGTHS AND CRCS

#ifndef MAVLINK_MESSAGE_LENGTHS
#define MAVLINK_MESSAGE_LENGTHS {}
#endif

#ifndef MAVLINK_MESSAGE_CRCS
#define MAVLINK_MESSAGE_CRCS {{30001, 54, 1, 1, 0, 0, 0}, {30002, 253, 1, 1, 0, 0, 0}, {30004, 135, 5, 5, 0, 0, 0}, {30005, 235, 1, 1, 0, 0, 0}, {30006, 91, 1, 1, 0, 0, 0}, {30007, 7, 2, 2, 0, 0, 0}, {30008, 78, 1, 1, 0, 0, 0}, {30010, 184, 1, 1, 0, 0, 0}, {30011, 85, 1, 1, 0, 0, 0}, {30012, 25, 1, 1, 0, 0, 0}, {30013, 165, 1, 1, 0, 0, 0}, {30014, 201, 4, 4, 0, 0, 0}, {30015, 86, 2, 2, 0, 0, 0}, {30016, 123, 1, 1, 0, 0, 0}, {30017, 51, 1, 1, 0, 0, 0}, {30018, 13, 5, 5, 0, 0, 0}, {30019, 137, 9, 9, 0, 0, 0}, {30020, 92, 1, 1, 0, 0, 0}, {30021, 113, 1, 1, 0, 0, 0}, {30022, 47, 1, 1, 0, 0, 0}, {30023, 74, 1, 1, 0, 0, 0}, {30024, 177, 1, 1, 0, 0, 0}, {30025, 234, 1, 1, 0, 0, 0}, {30026, 165, 1, 1, 0, 0, 0}, {30027, 33, 1, 1, 0, 0, 0}, {30028, 10, 1, 1, 0, 0, 0}, {30029, 44, 9, 9, 0, 0, 0}, {30030, 71, 28, 28, 0, 0, 0}, {30032, 149, 2, 2, 0, 0, 0}, {30033, 62, 2, 2, 0, 0, 0}, {30034, 8, 6, 6, 0, 0, 0}, {30035, 221, 1, 1, 0, 0, 0}, {30036, 32, 1, 1, 0, 0, 0}, {30037, 192, 6, 6, 0, 0, 0}, {30048, 40, 8, 8, 0, 0, 0}, {30049, 31, 1, 1, 0, 0, 0}, {30050, 63, 1, 1, 0, 0, 0}, {30051, 182, 1, 1, 0, 0, 0}, {30052, 107, 1, 1, 0, 0, 0}, {30062, 55, 32, 32, 0, 0, 0}, {30068, 107, 11, 11, 0, 0, 0}, {30070, 32, 1, 1, 0, 0, 0}, {30071, 207, 1, 1, 0, 0, 0}, {30072, 246, 1, 1, 0, 0, 0}, {30073, 154, 1, 1, 0, 0, 0}, {30074, 130, 2, 2, 0, 0, 0}, {30075, 41, 1, 1, 0, 0, 0}, {30076, 180, 1, 1, 0, 0, 0}, {30077, 39, 1, 1, 0, 0, 0}, {30078, 105, 1, 1, 0, 0, 0}, {30079, 61, 1, 1, 0, 0, 0}, {30081, 4, 1, 1, 0, 0, 0}, {30099, 60, 1, 1, 0, 0, 0}, {40001, 7, 12, 12, 0, 0, 0}, {40002, 49, 4, 4, 0, 0, 0}, {40004, 244, 1, 1, 0, 0, 0}, {40005, 119, 2, 2, 0, 0, 0}, {40006, 210, 1, 1, 0, 0, 0}, {40007, 231, 1, 1, 0, 0, 0}, {40008, 145, 1, 1, 0, 0, 0}, {40010, 104, 8, 8, 0, 0, 0}, {40011, 113, 1, 1, 0, 0, 0}, {40013, 192, 12, 12, 0, 0, 0}, {40014, 169, 6, 6, 0, 0, 0}, {40015, 206, 1, 1, 0, 0, 0}, {40016, 26, 1, 1, 0, 0, 0}, {40017, 43, 1, 1, 0, 0, 0}, {40018, 61, 6, 6, 0, 0, 0}, {40019, 191, 20, 20, 0, 0, 0}, {40020, 20, 12, 12, 0, 0, 0}, {40021, 134, 2, 2, 0, 0, 0}, {40022, 22, 2, 2, 0, 0, 0}, {40023, 133, 8, 8, 0, 0, 0}, {40024, 39, 2, 2, 0, 0, 0}, {40025, 166, 1, 1, 0, 0, 0}, {40026, 109, 1, 1, 0, 0, 0}, {40028, 152, 9, 9, 0, 0, 0}, {40029, 10, 2, 2, 0, 0, 0}, {40032, 149, 1, 1, 0, 0, 0}, {40033, 61, 1, 1, 0, 0, 0}, {40038, 227, 6, 6, 0, 0, 0}, {40039, 138, 1, 1, 0, 0, 0}, {40040, 66, 6, 6, 0, 0, 0}, {40041, 218, 7, 7, 0, 0, 0}, {40042, 223, 6, 6, 0, 0, 0}, {40048, 184, 1, 1, 0, 0, 0}, {40049, 65, 1, 1, 0, 0, 0}, {40050, 27, 1, 1, 0, 0, 0}, {40051, 206, 1, 1, 0, 0, 0}, {40052, 236, 1, 1, 0, 0, 0}, {40068, 133, 1, 1, 0, 0, 0}, {40070, 60, 1, 1, 0, 0, 0}, {40071, 235, 1, 1, 0, 0, 0}, {40072, 89, 1, 1, 0, 0, 0}, {40073, 192, 2, 2, 0, 0, 0}, {40074, 135, 2, 2, 0, 0, 0}, {40075, 207, 1, 1, 0, 0, 0}, {40076, 126, 1, 1, 0, 0, 0}, {40077, 151, 1, 1, 0, 0, 0}, {40078, 25, 1, 1, 0, 0, 0}, {40079, 139, 1, 1, 0, 0, 0}, {40080, 127, 10, 10, 0, 0, 0}, {40081, 199, 1, 1, 0, 0, 0}, {40099, 169, 1, 1, 0, 0, 0}, {300112, 159, 1, 1, 0, 0, 0}, {300113, 183, 1, 1, 0, 0, 0}, {300128, 14, 2, 2, 0, 0, 0}, {300129, 254, 1, 1, 0, 0, 0}, {300130, 194, 12, 12, 0, 0, 0}, {400112, 190, 1, 1, 0, 0, 0}, {400113, 98, 2, 2, 0, 0, 0}, {400128, 228, 2, 2, 0, 0, 0}, {400129, 2, 12, 12, 0, 0, 0}, {400130, 198, 1, 1, 0, 0, 0}}
#endif

#include "../protocol.h"

#define MAVLINK_ENABLED_GIMBAL

// ENUM DEFINITIONS



// MAVLINK VERSION

#ifndef MAVLINK_VERSION
#define MAVLINK_VERSION 2
#endif

#if (MAVLINK_VERSION == 0)
#undef MAVLINK_VERSION
#define MAVLINK_VERSION 2
#endif

// MESSAGE DEFINITIONS
#include "./mavlink_msg_request_firmware_version.h"
#include "./mavlink_msg_request_gimbal_hardware_id.h"
#include "./mavlink_msg_auto_focus.h"
#include "./mavlink_msg_manual_zoom_with_autofocus.h"
#include "./mavlink_msg_manual_focus.h"
#include "./mavlink_msg_gimbal_rotation_control.h"
#include "./mavlink_msg_one_key_centering.h"
#include "./mavlink_msg_request_camera_system_information.h"
#include "./mavlink_msg_function_feedback_response.h"
#include "./mavlink_msg_capture_photo_record_video.h"
#include "./mavlink_msg_request_gimbal_attitude_data.h"
#include "./mavlink_msg_set_gimbal_attitude_angles.h"
#include "./mavlink_msg_absolute_zoom_auto_focus.h"
#include "./mavlink_msg_request_video_stitching_mode.h"
#include "./mavlink_msg_set_video_stitching_mode.h"
#include "./mavlink_msg_get_temperature_at_selected_point.h"
#include "./mavlink_msg_local_temperature_measurement.h"
#include "./mavlink_msg_global_temperature_measurement.h"
#include "./mavlink_msg_request_laser_distance_measurement.h"
#include "./mavlink_msg_request_current_supported_zoom_range.h"
#include "./mavlink_msg_request_laser_distance_target_longitude_latitude.h"
#include "./mavlink_msg_request_current_zoom_magnification.h"
#include "./mavlink_msg_request_current_gimbal_mode.h"
#include "./mavlink_msg_request_current_thermal_image_pseudocolor.h"
#include "./mavlink_msg_set_current_thermal_image_pseudocolor.h"
#include "./mavlink_msg_request_camera_encoding_parameters.h"
#include "./mavlink_msg_set_camera_encoding_parameters.h"
#include "./mavlink_msg_send_aircraft_attitude_data_to_gimbal.h"
#include "./mavlink_msg_request_flight_controller_to_send_data_stream_to_gimbal.h"
#include "./mavlink_msg_request_gimbal_to_send_data_stream.h"
#include "./mavlink_msg_request_gimbal_to_send_laser_range_data_stream.h"
#include "./mavlink_msg_request_gimbal_magnetic_encoder_angle.h"
#include "./mavlink_msg_request_gimbal_control_mode.h"
#include "./mavlink_msg_request_weak_control_thresholds.h"
#include "./mavlink_msg_request_gimbal_motor_voltage_data.h"
#include "./mavlink_msg_set_utc_time.h"
#include "./mavlink_msg_request_system_info.h"
#include "./mavlink_msg_set_laser_state.h"
#include "./mavlink_msg_request_thermal_output_mode.h"
#include "./mavlink_msg_set_thermal_output_mode.h"
#include "./mavlink_msg_send_raw_gps_to_gimbal.h"
#include "./mavlink_msg_set_thermal_thresholds.h"
#include "./mavlink_msg_request_ir_threshold_precision.h"
#include "./mavlink_msg_set_ir_threshold_precision.h"
#include "./mavlink_msg_format_sd_card.h"
#include "./mavlink_msg_get_picture_name_type.h"
#include "./mavlink_msg_set_picture_name_type.h"
#include "./mavlink_msg_get_hdmi_osd_status.h"
#include "./mavlink_msg_set_hdmi_osd_status.h"
#include "./mavlink_msg_get_ai_mode_status.h"
#include "./mavlink_msg_get_ai_coordinate_stream_status.h"
#include "./mavlink_msg_update_thermal_shutter.h"
#include "./mavlink_msg_set_ai_coordinate_stream_status.h"
#include "./mavlink_msg_request_weak_control_mode.h"
#include "./mavlink_msg_set_weak_control_mode.h"
#include "./mavlink_msg_gimbal_camera_soft_reboot.h"
#include "./mavlink_msg_get_gimbal_camera_ip.h"
#include "./mavlink_msg_set_gimbal_camera_ip.h"
#include "./mavlink_msg_response_request_firmware_version.h"
#include "./mavlink_msg_response_request_gimbal_hardware_id.h"
#include "./mavlink_msg_response_auto_focus.h"
#include "./mavlink_msg_response_manual_zoom_with_autofocus.h"
#include "./mavlink_msg_response_manual_focus.h"
#include "./mavlink_msg_response_gimbal_rotation_control.h"
#include "./mavlink_msg_response_one_key_centering.h"
#include "./mavlink_msg_response_request_camera_system_information.h"
#include "./mavlink_msg_response_function_feedback_response.h"
#include "./mavlink_msg_response_request_gimbal_attitude_data.h"
#include "./mavlink_msg_response_set_gimbal_attitude_angles.h"
#include "./mavlink_msg_response_absolute_zoom_auto_focus.h"
#include "./mavlink_msg_response_request_video_stitching_mode.h"
#include "./mavlink_msg_response_set_video_stitching_mode.h"
#include "./mavlink_msg_response_get_temperature_at_selected_point.h"
#include "./mavlink_msg_response_local_temperature_measurement.h"
#include "./mavlink_msg_response_global_temperature_measurement.h"
#include "./mavlink_msg_response_request_laser_distance_measurement.h"
#include "./mavlink_msg_response_request_current_supported_zoom_range.h"
#include "./mavlink_msg_response_request_laser_distance_target_longitude_latitude.h"
#include "./mavlink_msg_response_request_current_zoom_magnification.h"
#include "./mavlink_msg_response_request_current_gimbal_mode.h"
#include "./mavlink_msg_response_request_current_thermal_image_pseudocolor.h"
#include "./mavlink_msg_response_camera_encoding_parameters.h"
#include "./mavlink_msg_response_set_camera_encoding_parameters.h"
#include "./mavlink_msg_response_request_flight_controller_to_send_data_stream_to_gimbal.h"
#include "./mavlink_msg_response_request_gimbal_to_send_data_stream.h"
#include "./mavlink_msg_response_request_gimbal_to_send_laser_range_data_stream.h"
#include "./mavlink_msg_response_encoder_angle.h"
#include "./mavlink_msg_response_gimbal_control_mode.h"
#include "./mavlink_msg_response_request_weak_control_thresholds.h"
#include "./mavlink_msg_response_gimbal_motor_voltage_1.h"
#include "./mavlink_msg_response_gimbal_motor_voltage_2.h"
#include "./mavlink_msg_response_set_utc_time.h"
#include "./mavlink_msg_response_request_system_info.h"
#include "./mavlink_msg_response_set_laser_state.h"
#include "./mavlink_msg_response_thermal_output_mode.h"
#include "./mavlink_msg_response_set_thermal_output_mode.h"
#include "./mavlink_msg_response_set_thermal_thresholds.h"
#include "./mavlink_msg_response_ir_threshold_precision.h"
#include "./mavlink_msg_response_set_ir_threshold_precision.h"
#include "./mavlink_msg_response_format_sd_card.h"
#include "./mavlink_msg_response_get_picture_name_type.h"
#include "./mavlink_msg_response_set_picture_name_type.h"
#include "./mavlink_msg_response_hdmi_osd_status.h"
#include "./mavlink_msg_response_set_hdmi_osd_status.h"
#include "./mavlink_msg_response_ai_mode_status.h"
#include "./mavlink_msg_response_ai_coordinate_stream_status.h"
#include "./mavlink_msg_response_update_thermal_shutter.h"
#include "./mavlink_msg_response_set_ai_coordinate_stream_status.h"
#include "./mavlink_msg_ai_coordinate_stream.h"
#include "./mavlink_msg_response_weak_control_mode.h"
#include "./mavlink_msg_response_set_weak_control_mode.h"
#include "./mavlink_msg_response_soft_reboot.h"
#include "./mavlink_msg_response_camera_ip.h"
#include "./mavlink_msg_response_set_camera_ip.h"

// base include



#if MAVLINK_GIMBAL_XML_HASH == MAVLINK_PRIMARY_XML_HASH
# define MAVLINK_MESSAGE_INFO {MAVLINK_MESSAGE_INFO_REQUEST_FIRMWARE_VERSION, MAVLINK_MESSAGE_INFO_REQUEST_GIMBAL_HARDWARE_ID, MAVLINK_MESSAGE_INFO_AUTO_FOCUS, MAVLINK_MESSAGE_INFO_MANUAL_ZOOM_WITH_AUTOFOCUS, MAVLINK_MESSAGE_INFO_MANUAL_FOCUS, MAVLINK_MESSAGE_INFO_GIMBAL_ROTATION_CONTROL, MAVLINK_MESSAGE_INFO_ONE_KEY_CENTERING, MAVLINK_MESSAGE_INFO_REQUEST_CAMERA_SYSTEM_INFORMATION, MAVLINK_MESSAGE_INFO_FUNCTION_FEEDBACK_RESPONSE, MAVLINK_MESSAGE_INFO_CAPTURE_PHOTO_RECORD_VIDEO, MAVLINK_MESSAGE_INFO_REQUEST_GIMBAL_ATTITUDE_DATA, MAVLINK_MESSAGE_INFO_SET_GIMBAL_ATTITUDE_ANGLES, MAVLINK_MESSAGE_INFO_ABSOLUTE_ZOOM_AUTO_FOCUS, MAVLINK_MESSAGE_INFO_REQUEST_VIDEO_STITCHING_MODE, MAVLINK_MESSAGE_INFO_SET_VIDEO_STITCHING_MODE, MAVLINK_MESSAGE_INFO_GET_TEMPERATURE_AT_SELECTED_POINT, MAVLINK_MESSAGE_INFO_LOCAL_TEMPERATURE_MEASUREMENT, MAVLINK_MESSAGE_INFO_GLOBAL_TEMPERATURE_MEASUREMENT, MAVLINK_MESSAGE_INFO_REQUEST_LASER_DISTANCE_MEASUREMENT, MAVLINK_MESSAGE_INFO_REQUEST_CURRENT_SUPPORTED_ZOOM_RANGE, MAVLINK_MESSAGE_INFO_REQUEST_LASER_DISTANCE_TARGET_LONGITUDE_LATITUDE, MAVLINK_MESSAGE_INFO_REQUEST_CURRENT_ZOOM_MAGNIFICATION, MAVLINK_MESSAGE_INFO_REQUEST_CURRENT_GIMBAL_MODE, MAVLINK_MESSAGE_INFO_REQUEST_CURRENT_THERMAL_IMAGE_PSEUDOCOLOR, MAVLINK_MESSAGE_INFO_SET_CURRENT_THERMAL_IMAGE_PSEUDOCOLOR, MAVLINK_MESSAGE_INFO_REQUEST_CAMERA_ENCODING_PARAMETERS, MAVLINK_MESSAGE_INFO_SET_CAMERA_ENCODING_PARAMETERS, MAVLINK_MESSAGE_INFO_SEND_AIRCRAFT_ATTITUDE_DATA_TO_GIMBAL, MAVLINK_MESSAGE_INFO_REQUEST_FLIGHT_CONTROLLER_TO_SEND_DATA_STREAM_TO_GIMBAL, MAVLINK_MESSAGE_INFO_REQUEST_GIMBAL_TO_SEND_DATA_STREAM, MAVLINK_MESSAGE_INFO_REQUEST_GIMBAL_MAGNETIC_ENCODER_ANGLE, MAVLINK_MESSAGE_INFO_REQUEST_GIMBAL_CONTROL_MODE, MAVLINK_MESSAGE_INFO_REQUEST_WEAK_CONTROL_THRESHOLDS, MAVLINK_MESSAGE_INFO_REQUEST_GIMBAL_MOTOR_VOLTAGE_DATA, MAVLINK_MESSAGE_INFO_SET_UTC_TIME, MAVLINK_MESSAGE_INFO_REQUEST_SYSTEM_INFO, MAVLINK_MESSAGE_INFO_SET_LASER_STATE, MAVLINK_MESSAGE_INFO_REQUEST_THERMAL_OUTPUT_MODE, MAVLINK_MESSAGE_INFO_SET_THERMAL_OUTPUT_MODE, MAVLINK_MESSAGE_INFO_SEND_RAW_GPS_TO_GIMBAL, MAVLINK_MESSAGE_INFO_SET_THERMAL_THRESHOLDS, MAVLINK_MESSAGE_INFO_REQUEST_IR_THRESHOLD_PRECISION, MAVLINK_MESSAGE_INFO_SET_IR_THRESHOLD_PRECISION, MAVLINK_MESSAGE_INFO_FORMAT_SD_CARD, MAVLINK_MESSAGE_INFO_GET_PICTURE_NAME_TYPE, MAVLINK_MESSAGE_INFO_SET_PICTURE_NAME_TYPE, MAVLINK_MESSAGE_INFO_GET_HDMI_OSD_STATUS, MAVLINK_MESSAGE_INFO_SET_HDMI_OSD_STATUS, MAVLINK_MESSAGE_INFO_GET_AI_MODE_STATUS, MAVLINK_MESSAGE_INFO_GET_AI_COORDINATE_STREAM_STATUS, MAVLINK_MESSAGE_INFO_UPDATE_THERMAL_SHUTTER, MAVLINK_MESSAGE_INFO_SET_AI_COORDINATE_STREAM_STATUS, MAVLINK_MESSAGE_INFO_REQUEST_GIMBAL_TO_SEND_LASER_RANGE_DATA_STREAM, MAVLINK_MESSAGE_INFO_RESPONSE_REQUEST_FIRMWARE_VERSION, MAVLINK_MESSAGE_INFO_RESPONSE_REQUEST_GIMBAL_HARDWARE_ID, MAVLINK_MESSAGE_INFO_RESPONSE_AUTO_FOCUS, MAVLINK_MESSAGE_INFO_RESPONSE_MANUAL_ZOOM_WITH_AUTOFOCUS, MAVLINK_MESSAGE_INFO_RESPONSE_MANUAL_FOCUS, MAVLINK_MESSAGE_INFO_RESPONSE_GIMBAL_ROTATION_CONTROL, MAVLINK_MESSAGE_INFO_RESPONSE_ONE_KEY_CENTERING, MAVLINK_MESSAGE_INFO_RESPONSE_REQUEST_CAMERA_SYSTEM_INFORMATION, MAVLINK_MESSAGE_INFO_RESPONSE_FUNCTION_FEEDBACK_RESPONSE, MAVLINK_MESSAGE_INFO_RESPONSE_REQUEST_GIMBAL_ATTITUDE_DATA, MAVLINK_MESSAGE_INFO_RESPONSE_SET_GIMBAL_ATTITUDE_ANGLES, MAVLINK_MESSAGE_INFO_RESPONSE_ABSOLUTE_ZOOM_AUTO_FOCUS, MAVLINK_MESSAGE_INFO_RESPONSE_REQUEST_VIDEO_STITCHING_MODE, MAVLINK_MESSAGE_INFO_RESPONSE_SET_VIDEO_STITCHING_MODE, MAVLINK_MESSAGE_INFO_RESPONSE_GET_TEMPERATURE_AT_SELECTED_POINT, MAVLINK_MESSAGE_INFO_RESPONSE_LOCAL_TEMPERATURE_MEASUREMENT, MAVLINK_MESSAGE_INFO_RESPONSE_GLOBAL_TEMPERATURE_MEASUREMENT, MAVLINK_MESSAGE_INFO_RESPONSE_REQUEST_LASER_DISTANCE_MEASUREMENT, MAVLINK_MESSAGE_INFO_RESPONSE_REQUEST_CURRENT_SUPPORTED_ZOOM_RANGE, MAVLINK_MESSAGE_INFO_RESPONSE_REQUEST_LASER_DISTANCE_TARGET_LONGITUDE_LATITUDE, MAVLINK_MESSAGE_INFO_RESPONSE_REQUEST_CURRENT_ZOOM_MAGNIFICATION, MAVLINK_MESSAGE_INFO_RESPONSE_REQUEST_CURRENT_GIMBAL_MODE, MAVLINK_MESSAGE_INFO_RESPONSE_REQUEST_CURRENT_THERMAL_IMAGE_PSEUDOCOLOR, MAVLINK_MESSAGE_INFO_RESPONSE_CAMERA_ENCODING_PARAMETERS, MAVLINK_MESSAGE_INFO_RESPONSE_SET_CAMERA_ENCODING_PARAMETERS, MAVLINK_MESSAGE_INFO_RESPONSE_REQUEST_FLIGHT_CONTROLLER_TO_SEND_DATA_STREAM_TO_GIMBAL, MAVLINK_MESSAGE_INFO_RESPONSE_REQUEST_GIMBAL_TO_SEND_DATA_STREAM, MAVLINK_MESSAGE_INFO_RESPONSE_ENCODER_ANGLE, MAVLINK_MESSAGE_INFO_RESPONSE_GIMBAL_CONTROL_MODE, MAVLINK_MESSAGE_INFO_RESPONSE_REQUEST_WEAK_CONTROL_THRESHOLDS, MAVLINK_MESSAGE_INFO_RESPONSE_GIMBAL_MOTOR_VOLTAGE_1, MAVLINK_MESSAGE_INFO_RESPONSE_GIMBAL_MOTOR_VOLTAGE_2, MAVLINK_MESSAGE_INFO_RESPONSE_SET_UTC_TIME, MAVLINK_MESSAGE_INFO_RESPONSE_REQUEST_SYSTEM_INFO, MAVLINK_MESSAGE_INFO_RESPONSE_SET_LASER_STATE, MAVLINK_MESSAGE_INFO_RESPONSE_THERMAL_OUTPUT_MODE, MAVLINK_MESSAGE_INFO_RESPONSE_SET_THERMAL_OUTPUT_MODE, MAVLINK_MESSAGE_INFO_RESPONSE_SET_THERMAL_THRESHOLDS, MAVLINK_MESSAGE_INFO_RESPONSE_IR_THRESHOLD_PRECISION, MAVLINK_MESSAGE_INFO_RESPONSE_SET_IR_THRESHOLD_PRECISION, MAVLINK_MESSAGE_INFO_RESPONSE_FORMAT_SD_CARD, MAVLINK_MESSAGE_INFO_RESPONSE_GET_PICTURE_NAME_TYPE, MAVLINK_MESSAGE_INFO_RESPONSE_SET_PICTURE_NAME_TYPE, MAVLINK_MESSAGE_INFO_RESPONSE_HDMI_OSD_STATUS, MAVLINK_MESSAGE_INFO_RESPONSE_SET_HDMI_OSD_STATUS, MAVLINK_MESSAGE_INFO_RESPONSE_AI_MODE_STATUS, MAVLINK_MESSAGE_INFO_RESPONSE_AI_COORDINATE_STREAM_STATUS, MAVLINK_MESSAGE_INFO_RESPONSE_UPDATE_THERMAL_SHUTTER, MAVLINK_MESSAGE_INFO_AI_COORDINATE_STREAM, MAVLINK_MESSAGE_INFO_RESPONSE_SET_AI_COORDINATE_STREAM_STATUS, MAVLINK_MESSAGE_INFO_RESPONSE_REQUEST_GIMBAL_TO_SEND_LASER_RANGE_DATA_STREAM, MAVLINK_MESSAGE_INFO_REQUEST_WEAK_CONTROL_MODE, MAVLINK_MESSAGE_INFO_SET_WEAK_CONTROL_MODE, MAVLINK_MESSAGE_INFO_GIMBAL_CAMERA_SOFT_REBOOT, MAVLINK_MESSAGE_INFO_GET_GIMBAL_CAMERA_IP, MAVLINK_MESSAGE_INFO_SET_GIMBAL_CAMERA_IP, MAVLINK_MESSAGE_INFO_RESPONSE_WEAK_CONTROL_MODE, MAVLINK_MESSAGE_INFO_RESPONSE_SET_WEAK_CONTROL_MODE, MAVLINK_MESSAGE_INFO_RESPONSE_SOFT_REBOOT, MAVLINK_MESSAGE_INFO_RESPONSE_CAMERA_IP, MAVLINK_MESSAGE_INFO_RESPONSE_SET_CAMERA_IP}
# define MAVLINK_MESSAGE_NAMES {{ "ABSOLUTE_ZOOM_AUTO_FOCUS", 30015 }, { "AI_COORDINATE_STREAM", 40080 }, { "AUTO_FOCUS", 30004 }, { "CAPTURE_PHOTO_RECORD_VIDEO", 30012 }, { "FORMAT_SD_CARD", 30072 }, { "FUNCTION_FEEDBACK_RESPONSE", 30011 }, { "GET_AI_COORDINATE_STREAM_STATUS", 30078 }, { "GET_AI_MODE_STATUS", 30077 }, { "GET_GIMBAL_CAMERA_IP", 300129 }, { "GET_HDMI_OSD_STATUS", 30075 }, { "GET_PICTURE_NAME_TYPE", 30073 }, { "GET_TEMPERATURE_AT_SELECTED_POINT", 30018 }, { "GIMBAL_CAMERA_SOFT_REBOOT", 300128 }, { "GIMBAL_ROTATION_CONTROL", 30007 }, { "GLOBAL_TEMPERATURE_MEASUREMENT", 30020 }, { "LOCAL_TEMPERATURE_MEASUREMENT", 30019 }, { "MANUAL_FOCUS", 30006 }, { "MANUAL_ZOOM_WITH_AUTOFOCUS", 30005 }, { "ONE_KEY_CENTERING", 30008 }, { "REQUEST_CAMERA_ENCODING_PARAMETERS", 30028 }, { "REQUEST_CAMERA_SYSTEM_INFORMATION", 30010 }, { "REQUEST_CURRENT_GIMBAL_MODE", 30025 }, { "REQUEST_CURRENT_SUPPORTED_ZOOM_RANGE", 30022 }, { "REQUEST_CURRENT_THERMAL_IMAGE_PSEUDOCOLOR", 30026 }, { "REQUEST_CURRENT_ZOOM_MAGNIFICATION", 30024 }, { "REQUEST_FIRMWARE_VERSION", 30001 }, { "REQUEST_FLIGHT_CONTROLLER_TO_SEND_DATA_STREAM_TO_GIMBAL", 30032 }, { "REQUEST_GIMBAL_ATTITUDE_DATA", 30013 }, { "REQUEST_GIMBAL_CONTROL_MODE", 30035 }, { "REQUEST_GIMBAL_HARDWARE_ID", 30002 }, { "REQUEST_GIMBAL_MAGNETIC_ENCODER_ANGLE", 30034 }, { "REQUEST_GIMBAL_MOTOR_VOLTAGE_DATA", 30037 }, { "REQUEST_GIMBAL_TO_SEND_DATA_STREAM", 30033 }, { "REQUEST_GIMBAL_TO_SEND_LASER_RANGE_DATA_STREAM", 30099 }, { "REQUEST_IR_THRESHOLD_PRECISION", 30070 }, { "REQUEST_LASER_DISTANCE_MEASUREMENT", 30021 }, { "REQUEST_LASER_DISTANCE_TARGET_LONGITUDE_LATITUDE", 30023 }, { "REQUEST_SYSTEM_INFO", 30049 }, { "REQUEST_THERMAL_OUTPUT_MODE", 30051 }, { "REQUEST_VIDEO_STITCHING_MODE", 30016 }, { "REQUEST_WEAK_CONTROL_MODE", 300112 }, { "REQUEST_WEAK_CONTROL_THRESHOLDS", 30036 }, { "RESPONSE_ABSOLUTE_ZOOM_AUTO_FOCUS", 40015 }, { "RESPONSE_AI_COORDINATE_STREAM_STATUS", 40078 }, { "RESPONSE_AI_MODE_STATUS", 40077 }, { "RESPONSE_AUTO_FOCUS", 40004 }, { "RESPONSE_CAMERA_ENCODING_PARAMETERS", 40028 }, { "RESPONSE_CAMERA_IP", 400129 }, { "RESPONSE_ENCODER_ANGLE", 40038 }, { "RESPONSE_FORMAT_SD_CARD", 40072 }, { "RESPONSE_FUNCTION_FEEDBACK_RESPONSE", 40011 }, { "RESPONSE_GET_PICTURE_NAME_TYPE", 40073 }, { "RESPONSE_GET_TEMPERATURE_AT_SELECTED_POINT", 40018 }, { "RESPONSE_GIMBAL_CONTROL_MODE", 40039 }, { "RESPONSE_GIMBAL_MOTOR_VOLTAGE_1", 40041 }, { "RESPONSE_GIMBAL_MOTOR_VOLTAGE_2", 40042 }, { "RESPONSE_GIMBAL_ROTATION_CONTROL", 40007 }, { "RESPONSE_GLOBAL_TEMPERATURE_MEASUREMENT", 40020 }, { "RESPONSE_HDMI_OSD_STATUS", 40075 }, { "RESPONSE_IR_THRESHOLD_PRECISION", 40070 }, { "RESPONSE_LOCAL_TEMPERATURE_MEASUREMENT", 40019 }, { "RESPONSE_MANUAL_FOCUS", 40006 }, { "RESPONSE_MANUAL_ZOOM_WITH_AUTOFOCUS", 40005 }, { "RESPONSE_ONE_KEY_CENTERING", 40008 }, { "RESPONSE_REQUEST_CAMERA_SYSTEM_INFORMATION", 40010 }, { "RESPONSE_REQUEST_CURRENT_GIMBAL_MODE", 40025 }, { "RESPONSE_REQUEST_CURRENT_SUPPORTED_ZOOM_RANGE", 40022 }, { "RESPONSE_REQUEST_CURRENT_THERMAL_IMAGE_PSEUDOCOLOR", 40026 }, { "RESPONSE_REQUEST_CURRENT_ZOOM_MAGNIFICATION", 40024 }, { "RESPONSE_REQUEST_FIRMWARE_VERSION", 40001 }, { "RESPONSE_REQUEST_FLIGHT_CONTROLLER_TO_SEND_DATA_STREAM_TO_GIMBAL", 40032 }, { "RESPONSE_REQUEST_GIMBAL_ATTITUDE_DATA", 40013 }, { "RESPONSE_REQUEST_GIMBAL_HARDWARE_ID", 40002 }, { "RESPONSE_REQUEST_GIMBAL_TO_SEND_DATA_STREAM", 40033 }, { "RESPONSE_REQUEST_GIMBAL_TO_SEND_LASER_RANGE_DATA_STREAM", 40099 }, { "RESPONSE_REQUEST_LASER_DISTANCE_MEASUREMENT", 40021 }, { "RESPONSE_REQUEST_LASER_DISTANCE_TARGET_LONGITUDE_LATITUDE", 40023 }, { "RESPONSE_REQUEST_SYSTEM_INFO", 40049 }, { "RESPONSE_REQUEST_VIDEO_STITCHING_MODE", 40016 }, { "RESPONSE_REQUEST_WEAK_CONTROL_THRESHOLDS", 40040 }, { "RESPONSE_SET_AI_COORDINATE_STREAM_STATUS", 40081 }, { "RESPONSE_SET_CAMERA_ENCODING_PARAMETERS", 40029 }, { "RESPONSE_SET_CAMERA_IP", 400130 }, { "RESPONSE_SET_GIMBAL_ATTITUDE_ANGLES", 40014 }, { "RESPONSE_SET_HDMI_OSD_STATUS", 40076 }, { "RESPONSE_SET_IR_THRESHOLD_PRECISION", 40071 }, { "RESPONSE_SET_LASER_STATE", 40050 }, { "RESPONSE_SET_PICTURE_NAME_TYPE", 40074 }, { "RESPONSE_SET_THERMAL_OUTPUT_MODE", 40052 }, { "RESPONSE_SET_THERMAL_THRESHOLDS", 40068 }, { "RESPONSE_SET_UTC_TIME", 40048 }, { "RESPONSE_SET_VIDEO_STITCHING_MODE", 40017 }, { "RESPONSE_SET_WEAK_CONTROL_MODE", 400113 }, { "RESPONSE_SOFT_REBOOT", 400128 }, { "RESPONSE_THERMAL_OUTPUT_MODE", 40051 }, { "RESPONSE_UPDATE_THERMAL_SHUTTER", 40079 }, { "RESPONSE_WEAK_CONTROL_MODE", 400112 }, { "SEND_AIRCRAFT_ATTITUDE_DATA_TO_GIMBAL", 30030 }, { "SEND_RAW_GPS_TO_GIMBAL", 30062 }, { "SET_AI_COORDINATE_STREAM_STATUS", 30081 }, { "SET_CAMERA_ENCODING_PARAMETERS", 30029 }, { "SET_CURRENT_THERMAL_IMAGE_PSEUDOCOLOR", 30027 }, { "SET_GIMBAL_ATTITUDE_ANGLES", 30014 }, { "SET_GIMBAL_CAMERA_IP", 300130 }, { "SET_HDMI_OSD_STATUS", 30076 }, { "SET_IR_THRESHOLD_PRECISION", 30071 }, { "SET_LASER_STATE", 30050 }, { "SET_PICTURE_NAME_TYPE", 30074 }, { "SET_THERMAL_OUTPUT_MODE", 30052 }, { "SET_THERMAL_THRESHOLDS", 30068 }, { "SET_UTC_TIME", 30048 }, { "SET_VIDEO_STITCHING_MODE", 30017 }, { "SET_WEAK_CONTROL_MODE", 300113 }, { "UPDATE_THERMAL_SHUTTER", 30079 }}
# if MAVLINK_COMMAND_24BIT
#  include "../mavlink_get_info.h"
# endif
#endif

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // MAVLINK_GIMBAL_H
