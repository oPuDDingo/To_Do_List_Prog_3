import {Component, OnInit} from '@angular/core';
import {Board} from "../../data-access/models/board";
import {List} from "../../data-access/models/list";
import {Reminder} from "../../data-access/models/reminder";
import {BackendService} from "../../data-access/services/backend.service";
import {ArrayUtil} from "../../util/ArrayUtil";


@Component({
    selector: 'board',
    templateUrl: './board.component.html',
    styleUrls: ['./board.component.scss']
})
export class BoardComponent implements OnInit {

    board: Board;
    currentList?: List;
    flagged: List;
    today: List;
    isFilterList: boolean;


    constructor(private service: BackendService) {
    }

    ngOnInit(): void {
        this.flagged = {title: "Flagged", reminders: []};
        this.today = {title: "Today", reminders: []};
        this.service.loadBoard().subscribe((board) => {
            this.board = board;
            this.updateFilterLists();
        });
    }

    selectList(list: List) : void {
        this.isFilterList = false;
        this.currentList = list;
    }

    createList() : void {
        let createdList : List = {title:"", reminders: []};
        this.board.lists.push(createdList);

        this.service.createList(createdList).subscribe((list) => {
            createdList.id = list.id;
        });
    }

    updateList(list: List) : void {
        this.service.updateList(list).subscribe();
    }

    deleteList(list: List) : void{
        ArrayUtil.cutElement(this.board.lists, list);

        if(this.currentList === list){
            this.currentList = undefined;
        }

        this.updateFilterLists();
        this.service.deleteList(list.id).subscribe();
    }

    createReminder(list: List) {
        let createdReminder : Reminder = {title: "", date:"", flagged: false};
        list.reminders.push(createdReminder);

        this.service.createReminder(list.id, createdReminder).subscribe((reminder) => {
           createdReminder.id = reminder.id;
        });
    }

    updateReminder(e : {list: List, reminder: Reminder}) : void {

        let listId : number = e.list.id;
        if(this.isFilterList) {
            listId = this.searchCorrectList(e.reminder).id;
        }

        this.updateFilterLists();
        this.service.updateReminder(listId, e.reminder).subscribe();
    }

    deleteReminder(e: {list: List, reminder: Reminder}) : void {
        ArrayUtil.cutElement(e.list.reminders, e.reminder);

        let listId : number = e.list.id;
        if(e.list == this.today || e.list == this.flagged) {
            let realList : List = this.searchCorrectList(e.reminder);
            ArrayUtil.cutElement(realList.reminders, e.reminder);
            listId = realList.id;
        }

        this.updateFilterLists();
        this.service.deleteReminder(listId, e.reminder.id).subscribe();
    }

    updateFilterLists() : void{
        this.flagged.reminders = [];
        this.today.reminders = [];
        for(var i = 0; i < this.board.lists.length; i++) {
            for(var j = 0; j < this.board.lists[i].reminders.length; j++){
                if(this.board.lists[i].reminders[j].flagged){
                    this.flagged.reminders.push(this.board.lists[i].reminders[j]);
                }
                if(this.board.lists[i].reminders[j].date === new Date().toISOString().split('T')[0]){
                    this.today.reminders.push(this.board.lists[i].reminders[j]);
                }
            }
        }
    }

    searchCorrectList(reminder: Reminder) : List {
        for(let i = 0; i < this.board.lists.length; i++){
            for(let j = 0; j < this.board.lists[i].reminders.length; j++){
                if(this.board.lists[i].reminders[j] == reminder){
                    return this.board.lists[i];
                }
            }
        }
    }

    selectToday(){
        this.isFilterList = true;
        this.updateFilterLists();
        this.currentList = this.today;
    }

    selectFlagged(){
        this.isFilterList = true;
        this.updateFilterLists();
        this.currentList = this.flagged;
    }


}
