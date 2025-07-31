#pragma once
// MESSAGE SET_THERMAL_THRESHOLDS PACKING

#define MAVLINK_MSG_ID_SET_THERMAL_THRESHOLDS 30068


typedef struct __mavlink_set_thermal_thresholds_t {
 int16_t thresh3_temp[2]; /*<  Min/Max temps (divide by 10)*/
 uint8_t thresh2_color[3]; /*<  RGB color of threshold region 2*/
 uint8_t thresh3_switch; /*<  0: hide, 1: display*/
 uint8_t thresh3_color[3]; /*<  RGB color of threshold region 3*/
} mavlink_set_thermal_thresholds_t;

#define MAVLINK_MSG_ID_SET_THERMAL_THRESHOLDS_LEN 11
#define MAVLINK_MSG_ID_SET_THERMAL_THRESHOLDS_MIN_LEN 11
#define MAVLINK_MSG_ID_30068_LEN 11
#define MAVLINK_MSG_ID_30068_MIN_LEN 11

#define MAVLINK_MSG_ID_SET_THERMAL_THRESHOLDS_CRC 107
#define MAVLINK_MSG_ID_30068_CRC 107

#define MAVLINK_MSG_SET_THERMAL_THRESHOLDS_FIELD_THRESH3_TEMP_LEN 2
#define MAVLINK_MSG_SET_THERMAL_THRESHOLDS_FIELD_THRESH2_COLOR_LEN 3
#define MAVLINK_MSG_SET_THERMAL_THRESHOLDS_FIELD_THRESH3_COLOR_LEN 3

#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_SET_THERMAL_THRESHOLDS { \
    30068, \
    "SET_THERMAL_THRESHOLDS", \
    4, \
    {  { "thresh2_color", NULL, MAVLINK_TYPE_UINT8_T, 3, 4, offsetof(mavlink_set_thermal_thresholds_t, thresh2_color) }, \
         { "thresh3_switch", NULL, MAVLINK_TYPE_UINT8_T, 0, 7, offsetof(mavlink_set_thermal_thresholds_t, thresh3_switch) }, \
         { "thresh3_temp", NULL, MAVLINK_TYPE_INT16_T, 2, 0, offsetof(mavlink_set_thermal_thresholds_t, thresh3_temp) }, \
         { "thresh3_color", NULL, MAVLINK_TYPE_UINT8_T, 3, 8, offsetof(mavlink_set_thermal_thresholds_t, thresh3_color) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_SET_THERMAL_THRESHOLDS { \
    "SET_THERMAL_THRESHOLDS", \
    4, \
    {  { "thresh2_color", NULL, MAVLINK_TYPE_UINT8_T, 3, 4, offsetof(mavlink_set_thermal_thresholds_t, thresh2_color) }, \
         { "thresh3_switch", NULL, MAVLINK_TYPE_UINT8_T, 0, 7, offsetof(mavlink_set_thermal_thresholds_t, thresh3_switch) }, \
         { "thresh3_temp", NULL, MAVLINK_TYPE_INT16_T, 2, 0, offsetof(mavlink_set_thermal_thresholds_t, thresh3_temp) }, \
         { "thresh3_color", NULL, MAVLINK_TYPE_UINT8_T, 3, 8, offsetof(mavlink_set_thermal_thresholds_t, thresh3_color) }, \
         } \
}
#endif

/**
 * @brief Pack a set_thermal_thresholds message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param thresh2_color  RGB color of threshold region 2
 * @param thresh3_switch  0: hide, 1: display
 * @param thresh3_temp  Min/Max temps (divide by 10)
 * @param thresh3_color  RGB color of threshold region 3
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_set_thermal_thresholds_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               const uint8_t *thresh2_color, uint8_t thresh3_switch, const int16_t *thresh3_temp, const uint8_t *thresh3_color)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SET_THERMAL_THRESHOLDS_LEN];
    _mav_put_uint8_t(buf, 7, thresh3_switch);
    _mav_put_int16_t_array(buf, 0, thresh3_temp, 2);
    _mav_put_uint8_t_array(buf, 4, thresh2_color, 3);
    _mav_put_uint8_t_array(buf, 8, thresh3_color, 3);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SET_THERMAL_THRESHOLDS_LEN);
#else
    mavlink_set_thermal_thresholds_t packet;
    packet.thresh3_switch = thresh3_switch;
    mav_array_assign_int16_t(packet.thresh3_temp, thresh3_temp, 2);
    mav_array_assign_uint8_t(packet.thresh2_color, thresh2_color, 3);
    mav_array_assign_uint8_t(packet.thresh3_color, thresh3_color, 3);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SET_THERMAL_THRESHOLDS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_SET_THERMAL_THRESHOLDS;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_SET_THERMAL_THRESHOLDS_MIN_LEN, MAVLINK_MSG_ID_SET_THERMAL_THRESHOLDS_LEN, MAVLINK_MSG_ID_SET_THERMAL_THRESHOLDS_CRC);
}

/**
 * @brief Pack a set_thermal_thresholds message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param thresh2_color  RGB color of threshold region 2
 * @param thresh3_switch  0: hide, 1: display
 * @param thresh3_temp  Min/Max temps (divide by 10)
 * @param thresh3_color  RGB color of threshold region 3
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_set_thermal_thresholds_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               const uint8_t *thresh2_color, uint8_t thresh3_switch, const int16_t *thresh3_temp, const uint8_t *thresh3_color)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SET_THERMAL_THRESHOLDS_LEN];
    _mav_put_uint8_t(buf, 7, thresh3_switch);
    _mav_put_int16_t_array(buf, 0, thresh3_temp, 2);
    _mav_put_uint8_t_array(buf, 4, thresh2_color, 3);
    _mav_put_uint8_t_array(buf, 8, thresh3_color, 3);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SET_THERMAL_THRESHOLDS_LEN);
#else
    mavlink_set_thermal_thresholds_t packet;
    packet.thresh3_switch = thresh3_switch;
    mav_array_memcpy(packet.thresh3_temp, thresh3_temp, sizeof(int16_t)*2);
    mav_array_memcpy(packet.thresh2_color, thresh2_color, sizeof(uint8_t)*3);
    mav_array_memcpy(packet.thresh3_color, thresh3_color, sizeof(uint8_t)*3);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SET_THERMAL_THRESHOLDS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_SET_THERMAL_THRESHOLDS;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_SET_THERMAL_THRESHOLDS_MIN_LEN, MAVLINK_MSG_ID_SET_THERMAL_THRESHOLDS_LEN, MAVLINK_MSG_ID_SET_THERMAL_THRESHOLDS_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_SET_THERMAL_THRESHOLDS_MIN_LEN, MAVLINK_MSG_ID_SET_THERMAL_THRESHOLDS_LEN);
#endif
}

/**
 * @brief Pack a set_thermal_thresholds message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param thresh2_color  RGB color of threshold region 2
 * @param thresh3_switch  0: hide, 1: display
 * @param thresh3_temp  Min/Max temps (divide by 10)
 * @param thresh3_color  RGB color of threshold region 3
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_set_thermal_thresholds_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   const uint8_t *thresh2_color,uint8_t thresh3_switch,const int16_t *thresh3_temp,const uint8_t *thresh3_color)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SET_THERMAL_THRESHOLDS_LEN];
    _mav_put_uint8_t(buf, 7, thresh3_switch);
    _mav_put_int16_t_array(buf, 0, thresh3_temp, 2);
    _mav_put_uint8_t_array(buf, 4, thresh2_color, 3);
    _mav_put_uint8_t_array(buf, 8, thresh3_color, 3);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SET_THERMAL_THRESHOLDS_LEN);
#else
    mavlink_set_thermal_thresholds_t packet;
    packet.thresh3_switch = thresh3_switch;
    mav_array_assign_int16_t(packet.thresh3_temp, thresh3_temp, 2);
    mav_array_assign_uint8_t(packet.thresh2_color, thresh2_color, 3);
    mav_array_assign_uint8_t(packet.thresh3_color, thresh3_color, 3);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SET_THERMAL_THRESHOLDS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_SET_THERMAL_THRESHOLDS;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_SET_THERMAL_THRESHOLDS_MIN_LEN, MAVLINK_MSG_ID_SET_THERMAL_THRESHOLDS_LEN, MAVLINK_MSG_ID_SET_THERMAL_THRESHOLDS_CRC);
}

/**
 * @brief Encode a set_thermal_thresholds struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param set_thermal_thresholds C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_set_thermal_thresholds_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_set_thermal_thresholds_t* set_thermal_thresholds)
{
    return mavlink_msg_set_thermal_thresholds_pack(system_id, component_id, msg, set_thermal_thresholds->thresh2_color, set_thermal_thresholds->thresh3_switch, set_thermal_thresholds->thresh3_temp, set_thermal_thresholds->thresh3_color);
}

/**
 * @brief Encode a set_thermal_thresholds struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param set_thermal_thresholds C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_set_thermal_thresholds_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_set_thermal_thresholds_t* set_thermal_thresholds)
{
    return mavlink_msg_set_thermal_thresholds_pack_chan(system_id, component_id, chan, msg, set_thermal_thresholds->thresh2_color, set_thermal_thresholds->thresh3_switch, set_thermal_thresholds->thresh3_temp, set_thermal_thresholds->thresh3_color);
}

/**
 * @brief Encode a set_thermal_thresholds struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param set_thermal_thresholds C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_set_thermal_thresholds_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_set_thermal_thresholds_t* set_thermal_thresholds)
{
    return mavlink_msg_set_thermal_thresholds_pack_status(system_id, component_id, _status, msg,  set_thermal_thresholds->thresh2_color, set_thermal_thresholds->thresh3_switch, set_thermal_thresholds->thresh3_temp, set_thermal_thresholds->thresh3_color);
}

/**
 * @brief Send a set_thermal_thresholds message
 * @param chan MAVLink channel to send the message
 *
 * @param thresh2_color  RGB color of threshold region 2
 * @param thresh3_switch  0: hide, 1: display
 * @param thresh3_temp  Min/Max temps (divide by 10)
 * @param thresh3_color  RGB color of threshold region 3
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_set_thermal_thresholds_send(mavlink_channel_t chan, const uint8_t *thresh2_color, uint8_t thresh3_switch, const int16_t *thresh3_temp, const uint8_t *thresh3_color)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SET_THERMAL_THRESHOLDS_LEN];
    _mav_put_uint8_t(buf, 7, thresh3_switch);
    _mav_put_int16_t_array(buf, 0, thresh3_temp, 2);
    _mav_put_uint8_t_array(buf, 4, thresh2_color, 3);
    _mav_put_uint8_t_array(buf, 8, thresh3_color, 3);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SET_THERMAL_THRESHOLDS, buf, MAVLINK_MSG_ID_SET_THERMAL_THRESHOLDS_MIN_LEN, MAVLINK_MSG_ID_SET_THERMAL_THRESHOLDS_LEN, MAVLINK_MSG_ID_SET_THERMAL_THRESHOLDS_CRC);
#else
    mavlink_set_thermal_thresholds_t packet;
    packet.thresh3_switch = thresh3_switch;
    mav_array_assign_int16_t(packet.thresh3_temp, thresh3_temp, 2);
    mav_array_assign_uint8_t(packet.thresh2_color, thresh2_color, 3);
    mav_array_assign_uint8_t(packet.thresh3_color, thresh3_color, 3);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SET_THERMAL_THRESHOLDS, (const char *)&packet, MAVLINK_MSG_ID_SET_THERMAL_THRESHOLDS_MIN_LEN, MAVLINK_MSG_ID_SET_THERMAL_THRESHOLDS_LEN, MAVLINK_MSG_ID_SET_THERMAL_THRESHOLDS_CRC);
#endif
}

/**
 * @brief Send a set_thermal_thresholds message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_set_thermal_thresholds_send_struct(mavlink_channel_t chan, const mavlink_set_thermal_thresholds_t* set_thermal_thresholds)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_set_thermal_thresholds_send(chan, set_thermal_thresholds->thresh2_color, set_thermal_thresholds->thresh3_switch, set_thermal_thresholds->thresh3_temp, set_thermal_thresholds->thresh3_color);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SET_THERMAL_THRESHOLDS, (const char *)set_thermal_thresholds, MAVLINK_MSG_ID_SET_THERMAL_THRESHOLDS_MIN_LEN, MAVLINK_MSG_ID_SET_THERMAL_THRESHOLDS_LEN, MAVLINK_MSG_ID_SET_THERMAL_THRESHOLDS_CRC);
#endif
}

#if MAVLINK_MSG_ID_SET_THERMAL_THRESHOLDS_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by reusing
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_set_thermal_thresholds_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  const uint8_t *thresh2_color, uint8_t thresh3_switch, const int16_t *thresh3_temp, const uint8_t *thresh3_color)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint8_t(buf, 7, thresh3_switch);
    _mav_put_int16_t_array(buf, 0, thresh3_temp, 2);
    _mav_put_uint8_t_array(buf, 4, thresh2_color, 3);
    _mav_put_uint8_t_array(buf, 8, thresh3_color, 3);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SET_THERMAL_THRESHOLDS, buf, MAVLINK_MSG_ID_SET_THERMAL_THRESHOLDS_MIN_LEN, MAVLINK_MSG_ID_SET_THERMAL_THRESHOLDS_LEN, MAVLINK_MSG_ID_SET_THERMAL_THRESHOLDS_CRC);
#else
    mavlink_set_thermal_thresholds_t *packet = (mavlink_set_thermal_thresholds_t *)msgbuf;
    packet->thresh3_switch = thresh3_switch;
    mav_array_assign_int16_t(packet->thresh3_temp, thresh3_temp, 2);
    mav_array_assign_uint8_t(packet->thresh2_color, thresh2_color, 3);
    mav_array_assign_uint8_t(packet->thresh3_color, thresh3_color, 3);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SET_THERMAL_THRESHOLDS, (const char *)packet, MAVLINK_MSG_ID_SET_THERMAL_THRESHOLDS_MIN_LEN, MAVLINK_MSG_ID_SET_THERMAL_THRESHOLDS_LEN, MAVLINK_MSG_ID_SET_THERMAL_THRESHOLDS_CRC);
#endif
}
#endif

#endif

// MESSAGE SET_THERMAL_THRESHOLDS UNPACKING


/**
 * @brief Get field thresh2_color from set_thermal_thresholds message
 *
 * @return  RGB color of threshold region 2
 */
static inline uint16_t mavlink_msg_set_thermal_thresholds_get_thresh2_color(const mavlink_message_t* msg, uint8_t *thresh2_color)
{
    return _MAV_RETURN_uint8_t_array(msg, thresh2_color, 3,  4);
}

/**
 * @brief Get field thresh3_switch from set_thermal_thresholds message
 *
 * @return  0: hide, 1: display
 */
static inline uint8_t mavlink_msg_set_thermal_thresholds_get_thresh3_switch(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  7);
}

/**
 * @brief Get field thresh3_temp from set_thermal_thresholds message
 *
 * @return  Min/Max temps (divide by 10)
 */
static inline uint16_t mavlink_msg_set_thermal_thresholds_get_thresh3_temp(const mavlink_message_t* msg, int16_t *thresh3_temp)
{
    return _MAV_RETURN_int16_t_array(msg, thresh3_temp, 2,  0);
}

/**
 * @brief Get field thresh3_color from set_thermal_thresholds message
 *
 * @return  RGB color of threshold region 3
 */
static inline uint16_t mavlink_msg_set_thermal_thresholds_get_thresh3_color(const mavlink_message_t* msg, uint8_t *thresh3_color)
{
    return _MAV_RETURN_uint8_t_array(msg, thresh3_color, 3,  8);
}

/**
 * @brief Decode a set_thermal_thresholds message into a struct
 *
 * @param msg The message to decode
 * @param set_thermal_thresholds C-struct to decode the message contents into
 */
static inline void mavlink_msg_set_thermal_thresholds_decode(const mavlink_message_t* msg, mavlink_set_thermal_thresholds_t* set_thermal_thresholds)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_set_thermal_thresholds_get_thresh3_temp(msg, set_thermal_thresholds->thresh3_temp);
    mavlink_msg_set_thermal_thresholds_get_thresh2_color(msg, set_thermal_thresholds->thresh2_color);
    set_thermal_thresholds->thresh3_switch = mavlink_msg_set_thermal_thresholds_get_thresh3_switch(msg);
    mavlink_msg_set_thermal_thresholds_get_thresh3_color(msg, set_thermal_thresholds->thresh3_color);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_SET_THERMAL_THRESHOLDS_LEN? msg->len : MAVLINK_MSG_ID_SET_THERMAL_THRESHOLDS_LEN;
        memset(set_thermal_thresholds, 0, MAVLINK_MSG_ID_SET_THERMAL_THRESHOLDS_LEN);
    memcpy(set_thermal_thresholds, _MAV_PAYLOAD(msg), len);
#endif
}
