
USE SAM_BACKBONE;

-- -----------------------------------------------------
-- Table TAB_AREAS
-- -----------------------------------------------------
INSERT INTO TAB_AREAS (name) VALUES ('manipulation');
INSERT INTO TAB_AREAS (name) VALUES ('navigation');

-- -----------------------------------------------------
-- Table TAB_MODULES
-- -----------------------------------------------------
  -- manipulation modules
INSERT INTO TAB_MODULES (area, module, symbol, name) VALUES (1, 1, 'J1_CON', 'JointControl h_shoulder');
INSERT INTO TAB_MODULES (area, module, symbol, name) VALUES (1, 2, 'J2_CON', 'JointControl v_shoulder');
INSERT INTO TAB_MODULES (area, module, symbol, name) VALUES (1, 3, 'J3_CON', 'JointControl elbow');
INSERT INTO TAB_MODULES (area, module, symbol, name) VALUES (1, 4, 'J4_CON', 'JointControl wrist');
INSERT INTO TAB_MODULES (area, module, symbol, name) VALUES (1, 5, 'J1_MOV', 'JointMover h_shoulder');
INSERT INTO TAB_MODULES (area, module, symbol, name) VALUES (1, 6, 'J2_MOV', 'JointMover v_shoulder');
INSERT INTO TAB_MODULES (area, module, symbol, name) VALUES (1, 7, 'J3_MOV', 'JointMover elbow');
INSERT INTO TAB_MODULES (area, module, symbol, name) VALUES (1, 8, 'J4_MOV', 'JointMover wrist');
INSERT INTO TAB_MODULES (area, module, symbol, name) VALUES (1, 9, 'ARMMOV', 'ArmMover');
-- navigation modules
-- INSERT INTO TAB_MODULES (area, module, symbol, name) VALUES (2, 1, 'NAVIG', 'Navigation');


-- -----------------------------------------------------
-- Table TAB_SENSES
-- -----------------------------------------------------
INSERT INTO TAB_SENSE (area, module, mod_symbol) 
select area, module, symbol from TAB_MODULES;


-- -----------------------------------------------------
-- Table TAB_CONTROLS
-- -----------------------------------------------------
INSERT INTO TAB_CONTROL (area, module, mod_symbol) 
select area, module, symbol from TAB_MODULES;

-- -----------------------------------------------------
-- Table TAB_SYMBOLS
-- -----------------------------------------------------
-- Manipulation area (1) - control symbols (cat 2)
INSERT INTO TAB_SYMBOLS (area, category, symbol, name) VALUES (1, 2, 'MOVPOS', 'JointMover: move in positive direction'); 
INSERT INTO TAB_SYMBOLS (area, category, symbol, name) VALUES (1, 2, 'MOVNEG', 'JointMover: move in negative direction'); 
INSERT INTO TAB_SYMBOLS (area, category, symbol, name) VALUES (1, 2, 'BRAKE', 'JointMover: brake action'); 
INSERT INTO TAB_SYMBOLS (area, category, symbol, name) VALUES (1, 2, 'START', 'ArmMover: start movement'); 
INSERT INTO TAB_SYMBOLS (area, category, symbol, name) VALUES (1, 2, 'STOP', 'ArmMover, JointMover: stop movement'); 

