Set vs_version=2013    :: 2012 or 2013 or 2015

goto case_%vs_version%              
:case_2012
  cd BehaviorTrees\                        
  "%VS110COMNTOOLS%..\IDE\devenv" StateMachine.sln /build Release
  goto end_case                  
:case_2013    
  cd BehaviorTrees\                        
  "%VS120COMNTOOLS%..\IDE\devenv" StateMachine.sln /build Release
  goto end_case
:case_2015            
  cd BehaviorTrees\                
  "%VS140COMNTOOLS%..\IDE\devenv" StateMachine.sln /build Release
  goto end_case
:end_case
  Copy Release\BehaviorTrees.exe .\
  cd ..
  pause