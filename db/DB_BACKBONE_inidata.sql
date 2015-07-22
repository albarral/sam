
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
INSERT INTO TAB_MODULES (areaID, moduleID, modul) VALUES (1, 1, 'shoulderpan mover');
INSERT INTO TAB_MODULES (areaID, moduleID, modul) VALUES (1, 2, 'shouldertilt mover');
INSERT INTO TAB_MODULES (areaID, moduleID, modul) VALUES (1, 3, 'elbow mover');
INSERT INTO TAB_MODULES (areaID, moduleID, modul) VALUES (1, 4, 'wrist mover');
-- navigation modules
--INSERT INTO TAB_MODULES (areaID, moduleID, modul) VALUES (2, 1, 'navigator');


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

