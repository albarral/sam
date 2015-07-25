
USE SAM_BACKBONE;

-- -----------------------------------------------------
-- Table TAB_AREAS
-- -----------------------------------------------------
INSERT INTO TAB_AREAS (area) VALUES ('manipulation');
INSERT INTO TAB_AREAS (area) VALUES ('navigation');

-- -----------------------------------------------------
-- Table TAB_MODULES
-- -----------------------------------------------------
-- manipulation modules
INSERT INTO TAB_MODULES (areaID, moduleID, modul) VALUES (1, 1, 'control h_shoulder');
INSERT INTO TAB_MODULES (areaID, moduleID, modul) VALUES (1, 2, 'control v_shoulder');
INSERT INTO TAB_MODULES (areaID, moduleID, modul) VALUES (1, 3, 'control elbow');
INSERT INTO TAB_MODULES (areaID, moduleID, modul) VALUES (1, 4, 'control wrist');
INSERT INTO TAB_MODULES (areaID, moduleID, modul) VALUES (1, 5, 'mover h_shoulder');
INSERT INTO TAB_MODULES (areaID, moduleID, modul) VALUES (1, 6, 'mover v_shoulder');
INSERT INTO TAB_MODULES (areaID, moduleID, modul) VALUES (1, 7, 'mover elbow');
INSERT INTO TAB_MODULES (areaID, moduleID, modul) VALUES (1, 8, 'mover wrist');
INSERT INTO TAB_MODULES (areaID, moduleID, modul) VALUES (1, 9, 'arm mover');
-- navigation modules
-- INSERT INTO TAB_MODULES (areaID, moduleID, modul) VALUES (2, 1, 'navigator');


-- -----------------------------------------------------
-- Table TAB_INFO
-- -----------------------------------------------------
INSERT INTO TAB_INFO (areaID, moduleID, modul) 
select areaID, moduleID, modul from TAB_MODULES;

-- -----------------------------------------------------
-- Table TAB_COMMANDS
-- -----------------------------------------------------
INSERT INTO TAB_COMMANDS (areaID, moduleID, modul) 
select areaID, moduleID, modul from TAB_MODULES;

