Set vs_version=2013    :: 2012 or 2013 or 2015

goto case_%vs_version%              
:case_2012
  cd StateMachine\                        
  "%VS110COMNTOOLS%..\IDE\devenv" StateMachine.sln /build Release
  goto end_case                  
:case_2013    
  cd StateMachine\                        
  "%VS120COMNTOOLS%..\IDE\devenv" StateMachine.sln /build Release
  goto end_case
:case_2015            
  cd StateMachine\                
  "%VS140COMNTOOLS%..\IDE\devenv" StateMachine.sln /build Release
  goto end_case
:end_case
  Copy Release\StateMachineProject.exe .\
  cd ..
  pause