
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
INSERT INTO TAB_MODULES (areaID, moduleID, modul) VALUES (1, 1, 'jointcontrol h_shoulder');
INSERT INTO TAB_MODULES (areaID, moduleID, modul) VALUES (1, 2, 'jointcontrol v_shoulder');
INSERT INTO TAB_MODULES (areaID, moduleID, modul) VALUES (1, 3, 'jointcontrol elbow');
INSERT INTO TAB_MODULES (areaID, moduleID, modul) VALUES (1, 4, 'jointcontrol wrist');
INSERT INTO TAB_MODULES (areaID, moduleID, modul) VALUES (1, 5, 'jointmover h_shoulder');
INSERT INTO TAB_MODULES (areaID, moduleID, modul) VALUES (1, 6, 'jointmover v_shoulder');
INSERT INTO TAB_MODULES (areaID, moduleID, modul) VALUES (1, 7, 'jointmover elbow');
INSERT INTO TAB_MODULES (areaID, moduleID, modul) VALUES (1, 8, 'jointmover wrist');
INSERT INTO TAB_MODULES (areaID, moduleID, modul) VALUES (1, 9, 'arm_mover');
-- navigation modules
-- INSERT INTO TAB_MODULES (areaID, moduleID, modul) VALUES (2, 1, 'navigator');


-- -----------------------------------------------------
-- Table TAB_SENSES
-- -----------------------------------------------------
INSERT INTO TAB_SENSES (areaID, moduleID, modul) 
select areaID, moduleID, modul from TAB_MODULES;

-- -----------------------------------------------------
-- Table TAB_CONTROLS
-- -----------------------------------------------------
INSERT INTO TAB_CONTROLS (areaID, moduleID, modul) 
select areaID, moduleID, modul from TAB_MODULES;

