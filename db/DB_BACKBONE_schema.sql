
DROP DATABASE IF EXISTS SAM_BACKBONE;
CREATE DATABASE IF NOT EXISTS SAM_BACKBONE;
USE SAM_BACKBONE;

-- -----------------------------------------------------
-- Table TAB_AREAS
-- -----------------------------------------------------
DROP TABLE IF EXISTS TAB_AREAS;

CREATE TABLE TAB_AREAS 
(
  area INT not NULL,
  name VARCHAR(30) not NULL
);

ALTER TABLE TAB_AREAS
ADD CONSTRAINT PK_AREAS PRIMARY KEY (area);

-- -----------------------------------------------------
-- Table TAB_MODULES
-- -----------------------------------------------------
DROP TABLE IF EXISTS TAB_MODULES;

CREATE TABLE TAB_MODULES
(
  area INT not NULL,
  module INT not NULL,
  symbol VARCHAR(6) not NULL,
  name VARCHAR(50) default null
);

ALTER TABLE TAB_MODULES
ADD CONSTRAINT PK_MODULES PRIMARY KEY (area, module);

-- -----------------------------------------------------
-- Table TAB_CONTROL
-- -----------------------------------------------------
DROP TABLE IF EXISTS TAB_CONTROL;

CREATE TABLE TAB_CONTROL 
(
  area INT not NULL,
  module INT not NULL,
  info INT default 0,
  detail INT default 0,
  proc INT default 0,
-- for debug purpose
  mod_symbol VARCHAR(6)
);

ALTER TABLE TAB_CONTROL 
ADD CONSTRAINT PK_CONTROL PRIMARY KEY (area, module);

-- -----------------------------------------------------
-- Table TAB_SENSE
-- -----------------------------------------------------
DROP TABLE IF EXISTS TAB_SENSE;

CREATE TABLE TAB_SENSE 
(
  area INT not NULL,
  module INT not NULL,
  info INT default 0,
  detail INT default 0,
  proc INT default 0,
-- for debug purpose
  mod_symbol VARCHAR(6)
);

ALTER TABLE TAB_SENSE 
ADD CONSTRAINT PK_SENSE PRIMARY KEY (area, module);

-- -----------------------------------------------------
-- Table TAB_SYMBOLS
-- -----------------------------------------------------
DROP TABLE IF EXISTS TAB_SYMBOLS;

CREATE TABLE TAB_SYMBOLS
(
  ID INT not NULL AUTO_INCREMENT,
  area INT not NULL,
  category INT not NULL,
  symbol VARCHAR(6) not NULL,
  name VARCHAR(50) default null,
  PRIMARY KEY (ID)
);




