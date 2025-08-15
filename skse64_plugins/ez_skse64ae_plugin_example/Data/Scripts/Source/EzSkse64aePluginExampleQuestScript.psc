Scriptname EzSkse64aePluginExampleQuestScript extends Quest  
{Ez SKSE64AE Plugin Example Quest Script}

; ========================================================
; IMPORTS ================================================
; ========================================================

import EzSkse64aeTestClass

; ========================================================
; VARIABLES ==============================================
; ========================================================

Int Property intTest = 1 Auto

Float Property floatTest = 1.0 Auto

Bool Property boolTest = False Auto

String Property stringTest = "One" Auto

; ========================================================
; EVENTS =================================================
; ========================================================

; For Skyrim, unlike Fallout4
; FIXME - called twice? prints 4 hello worlds
Event OnInit()
	Debug.Trace(self +" OnInit()")
	Debug.Notification("EzSkse64aePluginExampleQuest : OnInit")
	Debug.MessageBox("EzSkse64aePluginExampleQuest : OnInit")
	
	;code here
	
	;EzSkse64aeTestClass
	;EzSkse64aeTestClass.Test();
	
	if (EzSkse64aeTestClass.Test())
		Debug.Trace(self +" EzSkse64aeTestClass.Test()")
		Debug.Notification("EzSkse64aePluginExampleQuest : EzSkse64aeTestClass.Test()")
		Debug.MessageBox("EzSkse64aePluginExampleQuest : EzSkse64aeTestClass.Test()")
	endif
	
	if (Test())
		Debug.Trace(self +" Test()")
		Debug.Notification("EzSkse64aePluginExampleQuest : Test()")
		Debug.MessageBox("EzSkse64aePluginExampleQuest : Test()")
	endif
	
	Debug.Trace(self +" OnInit() : EOL")
	Debug.Notification("EzSkse64aePluginExampleQuest : OnInit : EOL")
	Debug.MessageBox("EzSkse64aePluginExampleQuest : OnInit : EOL")
EndEvent

Event OnReset()
	Debug.Trace(self +" OnReset()")
	Debug.Notification("EzSkse64aePluginExampleQuest : OnReset")
	Debug.MessageBox("EzSkse64aePluginExampleQuest : OnReset")
	
	;code here
	
	Debug.Trace(self +" OnReset() : EOL")
	Debug.Notification("EzSkse64aePluginExampleQuest : OnReset : EOL")
EndEvent

; Not used in Skyrim, unlike Fallout4
;Event OnQuestShutdown()
;	Debug.Trace(self +" OnQuestShutdown()")
;	Debug.Notification("EzSkse64aePluginExampleQuest : OnQuestShutdown")
;	Debug.MessageBox("EzSkse64aePluginExampleQuest : OnQuestShutdown")
;	
;	;code here
;	
;	Debug.Trace(self +" OnQuestShutdown() : EOL")
;	Debug.Notification("EzSkse64aePluginExampleQuest : OnQuestShutdown : EOL")
;EndEvent
