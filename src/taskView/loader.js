let taskList = {};
machine.readVariable('systemInfo:List', function (event, data) {
  machine[data].forEach(element => {
    if(element == '') return;
    taskList[element] = {}
    machine.readVariable(element+':task', function (event, data) {
        taskList[element] = Object.assign( taskList[element], {task:machine[data]}); 
    })
    machine.readVariable(element+':IO', function (event, data) {
        taskList[element] = Object.assign( taskList[element], {IO:machine[data]}); 
    })
    machine.readVariable(element+':Configuration', function (event, data) {
        taskList[element] = Object.assign( taskList[element], {Configuration:machine[data]}); 
    })
    updateTaskList()
  });
});

function updateTaskList(){
    document.querySelectorAll('.task-view').forEach(element => {                
        let partial = tmplits.get('tasklist-tmpl');
        element.innerHTML = partial(taskList);
        
    })
}
function selectTask(el, task){
    let readgroup = machine.getReadGroup('taskdebug')
    readgroup.data = {}
    machine.initCyclicReadGroup('taskdebug', task+':task');
    machine.initCyclicReadGroup('taskdebug', task+':IO');
    machine.initCyclicReadGroup('taskdebug', task+':Configuration');

    let scope = el.closest('.task-scope')
    scope.querySelectorAll('.task-item').forEach(element => {                
        element.classList.remove('selected')
    })
    el.classList.add('selected')

    scope.querySelectorAll('.task-details').forEach(element => {                
        let partial = tmplits.get('taskdetails-tmpl');
        let context = {};
        context[task] = taskList[task];
        element.innerHTML = partial(context);
        
    })    
}