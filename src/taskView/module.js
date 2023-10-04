import * as util from "../tmplits-utilities/module.js"

export function TmplitTaskView(context, args){
      //Pull out any attributes we need
    let {
        style = '', ..._args
    } = args.hash

    //Get cleaned values
    let {
        classList,
        attr
    } = util.cleanArgs(_args)
    classList = classList.concat(['task-view'])

    return `<div class='${classList.join(' ')}' style="${style}" ${attr}>Tasks</div>`
}