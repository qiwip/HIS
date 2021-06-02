/*
Navicat MySQL Data Transfer

Source Server         : wuqi
Source Server Version : 50718
Source Host           : localhost:3306
Source Database       : hospital

Target Server Type    : MYSQL
Target Server Version : 50718
File Encoding         : 65001

Date: 2017-06-23 15:09:00
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for dept_info
-- ----------------------------
DROP TABLE IF EXISTS `dept_info`;
CREATE TABLE `dept_info` (
  `id` varchar(255) NOT NULL,
  `name` varchar(255) NOT NULL,
  `director` varchar(255) NOT NULL,
  `location` varchar(255) NOT NULL,
  `introduction` varchar(255) NOT NULL,
  PRIMARY KEY (`id`,`name`),
  KEY `id` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Table structure for doctor_info
-- ----------------------------
DROP TABLE IF EXISTS `doctor_info`;
CREATE TABLE `doctor_info` (
  `id` varchar(255) NOT NULL,
  `name` varchar(255) NOT NULL,
  `sex` varchar(255) NOT NULL,
  `dept` varchar(255) NOT NULL,
  `title` varchar(255) NOT NULL,
  `level` int(10) unsigned NOT NULL,
  `account` varchar(255) NOT NULL,
  `password` varchar(255) NOT NULL,
  PRIMARY KEY (`id`,`account`),
  KEY `doctor_info` (`dept`),
  KEY `id` (`id`),
  CONSTRAINT `doctor_info` FOREIGN KEY (`dept`) REFERENCES `dept_info` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Table structure for medicine_list
-- ----------------------------
DROP TABLE IF EXISTS `medicine_list`;
CREATE TABLE `medicine_list` (
  `id` varchar(255) NOT NULL,
  `name` varchar(255) NOT NULL,
  `price` float(10,0) unsigned NOT NULL,
  `stock` int(10) unsigned NOT NULL,
  PRIMARY KEY (`id`,`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Table structure for outlay
-- ----------------------------
DROP TABLE IF EXISTS `outlay`;
CREATE TABLE `outlay` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `patient_id` varchar(255) NOT NULL,
  `item` varchar(255) NOT NULL,
  `price` float(11,0) NOT NULL,
  `number` int(11) NOT NULL,
  `total` float(11,0) NOT NULL,
  `date` datetime NOT NULL ON UPDATE CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=29 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Table structure for patient_info
-- ----------------------------
DROP TABLE IF EXISTS `patient_info`;
CREATE TABLE `patient_info` (
  `id` varchar(6) NOT NULL,
  `name` varchar(255) NOT NULL,
  `sex` varchar(4) NOT NULL,
  `id_card_no` char(18) NOT NULL,
  `phone` varchar(14) DEFAULT NULL,
  `password` varchar(255) NOT NULL,
  PRIMARY KEY (`id`,`id_card_no`),
  KEY `id` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Table structure for prescription
-- ----------------------------
DROP TABLE IF EXISTS `prescription`;
CREATE TABLE `prescription` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `patient_id` varchar(255) NOT NULL,
  `doctor_id` varchar(255) NOT NULL,
  `diagnose` longtext NOT NULL,
  `content` longtext NOT NULL,
  `date` datetime NOT NULL ON UPDATE CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=9 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Table structure for registration
-- ----------------------------
DROP TABLE IF EXISTS `registration`;
CREATE TABLE `registration` (
  `no` int(11) NOT NULL AUTO_INCREMENT,
  `patient_id` char(255) NOT NULL,
  `dept` varchar(255) NOT NULL,
  `doctor` varchar(255) NOT NULL,
  `flag` int(11) NOT NULL COMMENT '1为初诊',
  `date` datetime NOT NULL ON UPDATE CURRENT_TIMESTAMP,
  PRIMARY KEY (`no`),
  KEY `registration` (`patient_id`),
  KEY `reg1` (`dept`),
  KEY `reg2` (`doctor`),
  CONSTRAINT `reg1` FOREIGN KEY (`dept`) REFERENCES `dept_info` (`id`),
  CONSTRAINT `reg2` FOREIGN KEY (`doctor`) REFERENCES `doctor_info` (`id`),
  CONSTRAINT `registration` FOREIGN KEY (`patient_id`) REFERENCES `patient_info` (`id`) ON DELETE NO ACTION
) ENGINE=InnoDB AUTO_INCREMENT=8 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Table structure for test_list
-- ----------------------------
DROP TABLE IF EXISTS `test_list`;
CREATE TABLE `test_list` (
  `id` varchar(255) NOT NULL,
  `name` varchar(255) NOT NULL,
  `price` float(10,2) NOT NULL,
  PRIMARY KEY (`id`,`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Table structure for test_record
-- ----------------------------
DROP TABLE IF EXISTS `test_record`;
CREATE TABLE `test_record` (
  `no` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `done` int(11) NOT NULL,
  `doctor_id` varchar(255) NOT NULL,
  `patient_id` varchar(255) NOT NULL,
  `item` varchar(255) NOT NULL,
  `diagnose` longtext,
  `result` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`no`)
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Table structure for ward_list
-- ----------------------------
DROP TABLE IF EXISTS `ward_list`;
CREATE TABLE `ward_list` (
  `ward_no` varchar(255) NOT NULL,
  `bed_no` int(11) NOT NULL,
  `free` int(11) NOT NULL,
  `date` datetime(6) DEFAULT NULL ON UPDATE CURRENT_TIMESTAMP(6),
  `patient_id` varchar(255) DEFAULT NULL,
  `dept_id` varchar(255) NOT NULL,
  `price` int(10) NOT NULL,
  PRIMARY KEY (`ward_no`,`bed_no`),
  KEY `dapt` (`dept_id`),
  CONSTRAINT `dapt` FOREIGN KEY (`dept_id`) REFERENCES `dept_info` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
SET FOREIGN_KEY_CHECKS=1;
