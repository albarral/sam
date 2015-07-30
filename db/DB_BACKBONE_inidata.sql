
USE SAM_BACKBONE;

-- -----------------------------------------------------
-- Table TAB_AREAS
-- -----------------------------------------------------
delete from TAB_AREAS where area > 0;
INSERT INTO TAB_AREAS (area, name) VALUES (1, 'manipulation');
INSERT INTO TAB_AREAS (area, name) VALUES (2, 'navigation');

-- -----------------------------------------------------
-- Table TAB_MODULES
-- -----------------------------------------------------
delete from TAB_MODULES where area > 0;
  -- manipulation modules
INSERT INTO TAB_MODULES (area, module, symbol, name) VALUES (1, 0,   'AMANIP', 'Manipulation area');

INSERT INTO TAB_MODULES (area, module, symbol, name) VALUES (1, 1,   'J1_POS', 'JointControl h_shoulder');
INSERT INTO TAB_MODULES (area, module, symbol, name) VALUES (1, 2,   'J2_POS', 'JointControl v_shoulder');
INSERT INTO TAB_MODULES (area, module, symbol, name) VALUES (1, 3,   'J3_POS', 'JointControl elbow');
INSERT INTO TAB_MODULES (area, module, symbol, name) VALUES (1, 4,   'J4_POS', 'JointControl wrist');

INSERT INTO TAB_MODULES (area, module, symbol, name) VALUES (1, 5,   'J1_CON', 'JointControl h_shoulder');
INSERT INTO TAB_MODULES (area, module, symbol, name) VALUES (1, 6,   'J2_CON', 'JointControl v_shoulder');
INSERT INTO TAB_MODULES (area, module, symbol, name) VALUES (1, 7,   'J3_CON', 'JointControl elbow');
INSERT INTO TAB_MODULES (area, module, symbol, name) VALUES (1, 8,   'J4_CON', 'JointControl wrist');

INSERT INTO TAB_MODULES (area, module, symbol, name) VALUES (1, 9,   'J1_MOV', 'JointMover h_shoulder');
INSERT INTO TAB_MODULES (area, module, symbol, name) VALUES (1, 10, 'J2_MOV', 'JointMover v_shoulder');
INSERT INTO TAB_MODULES (area, module, symbol, name) VALUES (1, 11, 'J3_MOV', 'JointMover elbow');
INSERT INTO TAB_MODULES (area, module, symbol, name) VALUES (1, 12, 'J4_MOV', 'JointMover wrist');

INSERT INTO TAB_MODULES (area, module, symbol, name) VALUES (1, 13, 'ARMMOV', 'ArmMover');
-- navigation modules
-- INSERT INTO TAB_MODULES (area, module, symbol, name) VALUES (2, 1, 'NAVIG', 'Navigation');


-- -----------------------------------------------------
-- Table TAB_SENSES
-- -----------------------------------------------------
delete from TAB_SENSE where area > 0;
INSERT INTO TAB_SENSE (area, module, mod_symbol, proc) 
select area, module, symbol, -1 from TAB_MODULES;


-- -----------------------------------------------------
-- Table TAB_CONTROLS
-- -----------------------------------------------------
delete from TAB_CONTROL where area > 0;
INSERT INTO TAB_CONTROL (area, module, mod_symbol, proc) 
select area, module, symbol, -1 from TAB_MODULES;

-- -----------------------------------------------------
-- Table TAB_SYMBOLS
-- -----------------------------------------------------
delete from TAB_SYMBOLS where ID > 0;
-- general controls
INSERT INTO TAB_SYMBOLS (area, category, symbol, name) VALUES (0, 2, 'START', 'start anything'); 
INSERT INTO TAB_SYMBOLS (area, category, symbol, name) VALUES (0, 2, 'STOP', 'stop anything'); 
INSERT INTO TAB_SYMBOLS (area, category, symbol, name) VALUES (0, 2, 'FINISH', 'finish all modules in an area'); 
-- Manipulation controls
INSERT INTO TAB_SYMBOLS (area, category, symbol, name) VALUES (1, 2, 'MOVPOS', 'JointMover: move in positive direction'); 
INSERT INTO TAB_SYMBOLS (area, category, symbol, name) VALUES (1, 2, 'MOVNEG', 'JointMover: move in negative direction'); 
INSERT INTO TAB_SYMBOLS (area, category, symbol, name) VALUES (1, 2, 'MOVBRA', 'JointMover: brake action'); 

