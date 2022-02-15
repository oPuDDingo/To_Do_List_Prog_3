import {Component, OnInit} from '@angular/core';
import {Board} from "../../data-access/models/board";
import {List} from "../../data-access/models/list";
import {Reminder} from "../../data-access/models/reminder";
import {BackendService} from "../../data-access/services/backend.service";


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
        })
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
        console.log("update list");
    }

    deleteList(list: List) : void{
        let i: number = this.board.lists.indexOf(list);
        this.board.lists.splice(i, 1);
        if(this.currentList === list){
            this.currentList = undefined;
        }
        this.service.deleteList(list.id).subscribe();
    }

    createReminder(list: List) {
        let createdReminder : Reminder = {title: "", date:"", flagged: false};
        list.reminders.push(createdReminder);
    }

    updateReminder(e : {list: List, reminder: Reminder}) : void {
        console.log("update reminder");
    }

    deleteReminder(e: {list: List, reminder: Reminder}) : void {
        let i : number = e.list.reminders.indexOf(e.reminder);
        e.list.reminders.splice(i, 1);

        /*
        outer:
        for(var i = 0; i < this.board.lists.length; i++){
            for(var j = 0; j < this.board.lists[i].reminders.length; j++){
                if(this.board.lists[i].reminders[j] == reminder){
                    this.board.lists[i].reminders.splice(j, 1);
                    break outer;
                }
            }
        }
        */
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
