
DROP DATABASE IF EXISTS SAM_BACKBONE;
CREATE DATABASE IF NOT EXISTS SAM_BACKBONE;
USE SAM_BACKBONE;

-- -----------------------------------------------------
-- Table TAB_AREAS
-- -----------------------------------------------------
DROP TABLE IF EXISTS TAB_AREAS;

CREATE TABLE TAB_AREAS 
(
  ID INT not NULL AUTO_INCREMENT,
  area VARCHAR(30),
  PRIMARY KEY (ID)
);

-- -----------------------------------------------------
-- Table TAB_MODULES
-- -----------------------------------------------------
DROP TABLE IF EXISTS TAB_MODULES;

CREATE TABLE TAB_MODULES
(
  areaID INT not NULL,
  moduleID INT not NULL,
  modul VARCHAR(30),
  PRIMARY KEY (areaID, moduleID)
);

-- -----------------------------------------------------
-- Table TAB_INFO
-- -----------------------------------------------------
DROP TABLE IF EXISTS TAB_INFO;

CREATE TABLE TAB_INFO 
(
  areaID INT not NULL,
  moduleID INT not NULL,
  modul VARCHAR(30) not NULL,  
  info VARCHAR(40),
  detail INT default 0,
  proc INT default 0,
  PRIMARY KEY (areaID, moduleID)
);

-- -----------------------------------------------------
-- Table TAB_COMMANDS
-- -----------------------------------------------------
DROP TABLE IF EXISTS TAB_COMMANDS;

CREATE TABLE TAB_COMMANDS 
(
  areaID INT not NULL,
  moduleID INT not NULL,
  modul VARCHAR(30) not NULL,
  info VARCHAR(40),
  detail INT default 0,
  proc INT default 0,
  PRIMARY KEY (areaID, moduleID)
);

