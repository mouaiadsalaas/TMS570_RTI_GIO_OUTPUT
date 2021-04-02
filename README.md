# TMS570_RTI_GIO_OUTPUT

please follow these steps:

/*In HALCOGEN*/ 
*   @b Step @b 1:
*
*   Create a new project.
*
*   Navigate: -> File -> New -> Project
*
*   @image html example_createProject.jpg "Figure: Create a new Project"
*
*   @b Step @b 2:
*
*   Configure driver code generation: 
*   - Enable RTI driver
*   - Enable GIO driver
*   - Disable others
*
*   Navigate: -> TMS570LSxx /RM4 -> Enable Drivers
*
*   @image html example_rtiBlinky_enableDrivers.jpg "Figure: Driver Configuration"
*
*   @b Step @b 3:
*
*   Configure Vectored Interrupt Module Channels: 
*   - Map VIM Channel 2 to RTI Compare 0 interrupt
*   - Enable VIM Channel 2
*   - Map VIM Channel 2 to IRQ
*
*   Navigate: -> TMS570LSxx /RM4 -> VIM Channel 0-31
*
*   @image html example_rtiBlinky_vimChannelView.jpg "Figure: VIM Channel Configuration"
*
*   @b Step @b 4:
*
*   Configure RTI compare 0 period to 1000 ms: 
*   - Enter 1000.000 to Compare 0 Period edit box
*
*   Navigate: -> RTI -> RTI1 Compare
*
*   @image html example_rtiBlinky_rti1CompareView.jpg "Figure: RTI Compare Configuration"
*
*   @b Step @b 5:
*
*   Generate code
*
*   Navigate: -> File -> Generate Code
*
*   @image html generateCode.jpg "Figure: Generate Code"
/*In CODE COMPOSER STUDIO*/ 

Step 6:

Navigate: -> File -> NEW -> CCS project 
then in the window Navigate: -> target -> TMS570LS04x 
Navigate: -> Connection -> texas instruments XDS100v2 USB Debug probe 

Step 7:

in project properties
Navigate: -> include option -> add include file from the code we generate in HALCOGEN
Navigate: -> advanced option -> language -> change it to c99
Navigate: -> Debug -> Flash option -> erase option -> neccessry only

Step 8:

then write the code i have been added here

